using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Threading.Tasks;

namespace MSIL
{
    public class Program
    {
        public static int Main(string[] args)
        {
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

            Console.WriteLine("Using Keyfile: " + args[0]);

            string programFiles = Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86),
                   ildasm = Path.Combine(programFiles, @"Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\ildasm.exe");
            if (!File.Exists(ildasm))
            {
                var err = $"Windows 8.1A SDK or .Net Framework SDK 4.5.1 is required to build library - it was not found at '{ildasm}'";
                Console.WriteLine(err);
                throw new FileNotFoundException(err);
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
            string resPath = Path.Combine(compiledPath, "Enums.res");
            if (!File.Exists(dllPath))
                ThrowPathError("Could not locate compiled file", dllPath);

            Console.WriteLine(Launch(ildasm, $"/TEXT /OUT=\"{ilPath}\" \"{dllPath}\""));

            ReWrite(ilPath);

            Console.WriteLine(Launch(ilasm, $"/OUTPUT=\"{dllPath}\" /PDB /DLL \"{ilPath}\" /RES=\"{resPath}\" /KEY=" + args[0]));
            return 0;
        }

        private static void ReWrite(string path)
        {
            if (!File.Exists(path))
                ThrowPathError("Failed to find disassembled file at ", path);

            var newSource = new List<string>();
            var lines = File.ReadAllLines(path);

            bool foundMethodHeading = false, foundMethodBrace = false, writtenReplacement = false;
            foreach (var line in lines)
            {
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

                foundMethodHeading = false;
                foundMethodBrace = false;
                writtenReplacement = false;
                newSource.Add(line);
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
