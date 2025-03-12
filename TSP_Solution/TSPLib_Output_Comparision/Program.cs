using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
class Program
{
    static void Main()
    {
        List<(string Name, double Number)> a = TheirFile();
        List<(string Name, double Number)> b = MyFile();


        double totalDistanceA = 0;
        double totalDistanceB = 0;

        Console.WriteLine("Numerical distances for matching names:");
        foreach (var entry in b)
        {
            var match = a.FirstOrDefault(x => x.Name == entry.Name);
            totalDistanceA += entry.Number;
            totalDistanceB += match.Number;
            if (match != default)
            {
                double distance = Math.Abs(entry.Number - match.Number);
                Console.WriteLine($"Name: {entry.Name}, Difference: {distance}, percentage: {entry.Number / match.Number}");
            }
        }

        Console.WriteLine($"Distance total: {totalDistanceB}, My Distance: {totalDistanceA}, difference: {totalDistanceA / totalDistanceB}");
    }

    static List<(string Name, double Number)> TheirFile()
    {
        string filePath = "C:\\Users\\andre\\OneDrive\\University\\Dissertation\\Data\\STSP_TSPLib_results.txt"; // Change this to your file path
        List<(string Name, double Number)> dataList = new List<(string, double)>();

        try
        {
            foreach (string line in File.ReadLines(filePath))
            {
                string[] parts = line.Split(':');
                if (parts.Length == 2 && double.TryParse(parts[1].Trim(), out double number))
                {
                    dataList.Add((parts[0].Trim(), number));
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error reading file: {ex.Message}");
        }
        return dataList;
    }

    static List<(string Name, double Number)> MyFile()
    {
        string filePath = "C:\\Users\\andre\\OneDrive\\University\\Dissertation\\Data\\TSPLib_output.txt"; // Change this to your file path
        List<(string Name, double Number)> dataList = new List<(string, double)>();

        try
        {
            bool processEqualSign = false;
            foreach (string line in File.ReadLines(filePath))
            {
                if (processEqualSign)
                {
                    string[] parts = line.Split('=');
                    if (parts.Length == 2 && double.TryParse(parts[1].Trim(), out double number))
                    {
                        string name = parts[0].Trim().Replace(".tsp", "");
                        dataList.Add((name, number));
                    }
                }
                processEqualSign = !processEqualSign;
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error reading file: {ex.Message}");
        }
        return dataList;
    }
}