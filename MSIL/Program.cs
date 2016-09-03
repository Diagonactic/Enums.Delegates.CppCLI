using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace MSIL
{
    public class Program
    {
        public static int Main(string[] args)
        {
            Console.WriteLine("Processing MSIL for Enums");
            if (args.Length != 1)
            {
                Console.WriteLine("ERROR: No keyfile was included for signing the assembly");
                return 1;
            }
            if (!File.Exists(args[0]))
            {
                Console.WriteLine("ERROR: Keyfile " + args[0] + " was not found");
                return 1;
            }

            Console.WriteLine("INFORMATION: Using Keyfile: " + args[0]);

            string programFiles = Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86),
                   ildasm = Path.Combine(programFiles, @"Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\ildasm.exe");
            if (!File.Exists(ildasm))
            {
                Console.WriteLine($"ERROR: Windows 8.1A SDK or .Net Framework SDK 4.5.1 is required to build library - it was not found at '{ildasm}'");
                return 1;
            }

            string ilasm = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Windows), @"Microsoft.NET\Framework64\v4.0.30319\ilasm.exe");
            if (!File.Exists(ilasm))
                ThrowPathError(".Net Framework 4.5 is required to build library - it was not found at", ilasm);

            string compiledPath = @"..\x64\Release";
            string pathError = "Couldn't locate release binary path";
            if (!Directory.Exists(compiledPath))
            {
                Console.WriteLine(GetPathErrorValue("INFO: " + pathError, compiledPath));
                compiledPath = @"..\..\..\x64\Release";
                if (!Directory.Exists(compiledPath))
                {
                    Console.WriteLine(GetPathErrorValue("INFO: " + pathError, compiledPath));
                    compiledPath = @"..\..\x64\Release";
                    if (!Directory.Exists(compiledPath))
                        ThrowPathError("ERROR: " + pathError, compiledPath);
                }
            }

            string dllPath = Path.Combine(compiledPath, "Enums.dll");
            string ilPath = Path.Combine(compiledPath, "Enums.il");
            string xmlPath = Path.Combine(compiledPath, "Enums.xml");
            string resPath = Path.Combine(compiledPath, "Enums.res");
            if (!File.Exists(dllPath))
                ThrowPathError("Could not locate compiled file", dllPath);

            Console.WriteLine(Launch(ildasm, $"/TEXT /OUT=\"{ilPath}\" \"{dllPath}\""));

            ReWrite(ilPath);
            var result = File.ReadAllText(xmlPath);
            var newFile = s_Pdm.Replace(result, "ParameterizedEnumDelegateMap");
            File.WriteAllText(xmlPath, newFile);
            Console.WriteLine(Launch(ilasm, $"/OUTPUT=\"{dllPath}\" /PDB /DLL \"{ilPath}\" /RES=\"{resPath}\" /KEY=" + args[0]));

            return 0;
        }

        private static string BundleOverloadedClass(string className, string lineOfCil)
        {
            var rx = new Regex(className + "[0-9]");
            if (lineOfCil.Contains(className))
            {
                var match = rx.Match(lineOfCil);
                if (match.Success)
                {
                    Console.WriteLine($"Message: Bundled Overloaded Class '{match.Value}' to '{lineOfCil}'");
                    return rx.Replace(lineOfCil, className);
                }
            }
            return lineOfCil;
        }
        static readonly Regex s_Pdm = new Regex("ParameterizedEnumDelegateMap[0-9]");

        private static bool CheckLineForOverloadedClass(List<string> newSource, string className, string lineOfCil)
        {
            if (newSource == null) throw new ArgumentNullException(nameof(newSource));
            if (!lineOfCil.Contains(className))
                return false;

            var newLine = BundleOverloadedClass(className, lineOfCil);

            newSource.Add(newLine);
            return newLine != lineOfCil;
        }
        private static void ReWrite(string path)
        {
            if (!File.Exists(path))
                ThrowPathError("Failed to find disassembled file at ", path);

            var newSource = new List<string>();
            var lines = File.ReadAllLines(path);
            bool successEnumDelegateMap = false, successEnumClobber = false;
            bool foundMethodHeading = false, foundMethodBrace = false, writtenReplacement = false;
            foreach (var line in lines)
            {

                if (CheckLineForOverloadedClass(newSource, "ParameterizedEnumDelegateMap", line))
                {
                    successEnumDelegateMap = true;
                    continue;
                }
                
                if (line.Contains("ClobberFrom<"))
                {
                    foundMethodHeading = true;
                    newSource.Add(line);
                    continue;
                }
                if (foundMethodHeading && line.Contains("{"))
                {
                    foundMethodBrace = true;
                    continue;
                }
                if (foundMethodHeading && foundMethodBrace)
                {
                    if (!writtenReplacement)
                    {
                        if (!line.Contains("// Code size") && !line.Contains("(0x16)"))
                            throw new InvalidOperationException("Enums.il was not in the expected format.");
                        newSource.AddRange(new[]
                                           {
                                           "  {",
                                           "\t.maxstack 1",
                                           "\tIL_0000:  ldarg.0",
                                           "\tIL_0001:  ret"
                                       });
                        writtenReplacement = true;
                        continue;
                    }
                    else if (!line.Contains("}"))
                        continue;
                }
                if (writtenReplacement)
                    successEnumClobber = true;

                foundMethodHeading = false;
                foundMethodBrace = false;
                writtenReplacement = false;
                newSource.Add(line);
            }
            if (!successEnumClobber || !successEnumDelegateMap)
            {
                Console.WriteLine($"Error - Found Clobber Methods: {successEnumClobber}, Found ParameterizedEnumDelegateMap: {successEnumDelegateMap}");
                Environment.Exit(5);
            }
            File.WriteAllLines(path, newSource);
        }

        private static string Launch(string executable, string parameters)
        {
            var proc = new Process
                       {
                           StartInfo = new ProcessStartInfo(executable, parameters)
                                       {
                                           WindowStyle = ProcessWindowStyle.Hidden,
                                           RedirectStandardError = true,
                                           UseShellExecute = false,
                                           CreateNoWindow = true,
                                           RedirectStandardOutput = true
                                       }
                       };
            proc.Start();
            
            string output = proc.StandardOutput.ReadToEnd(),
                   error = proc.StandardError.ReadToEnd();
            if (!string.IsNullOrWhiteSpace(error))
                throw new Exception($"ERROR: {executable} {parameters}\r\n{error}");
            proc.WaitForExit();
            return output;
        }

        private static string GetPathErrorValue(string val, string path)
        {
            return $"{val} '{path}' (Current Directry: {Directory.GetCurrentDirectory()})";
        }

        private static void ThrowPathError(string val, string path)
        {
            string err = GetPathErrorValue(val, path);
            Console.WriteLine(err);
            throw new FileNotFoundException(err);
        }
    }
}
