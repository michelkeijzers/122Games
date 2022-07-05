using System.Linq;
using System.Text;
using System.Windows;
using System.Collections.Generic;
using System.IO;

namespace WebsiteXTestInc
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly string PATH =
            @"C:\users\miche\source\repos\122Games";
        private readonly string FORMAT_STRING = "{0, -70} {1, 6:N0}\n";
        private readonly string header =
            "---------------------------------------------------------------------- ------\n";
        private int _totalLines = 0;


        public MainWindow()
        {
            InitializeComponent();
            StringBuilder builder = new StringBuilder().AppendLine(header).Append(
                string.Format(FORMAT_STRING, "File Name", "#Lines") + header);
            Traverse(builder, PATH);
            string totalLines = string.Format(FORMAT_STRING, "Total Lines", _totalLines);
            builder.Append(header).Append(totalLines);
            _textBlock.Text = totalLines + builder.ToString();
        }


        private void Traverse(StringBuilder builder, string path)
        {
            AddFiles(builder, path, "*.h");
            AddFiles(builder, path, "*.cpp");
            AddFiles(builder, path, "*.htm");
            AddFiles(builder, path, "*.html");
            AddFiles(builder, path, "*.css");
            AddFiles(builder, path, "*.txt");
            foreach (string directory in Directory.GetDirectories(path))
            {
                if (!directory.EndsWith(".git") &&
                    !directory.EndsWith("obj") &&
                    !directory.EndsWith("bin"))
                {
                    Traverse(builder, directory);
                }
            }
        }


        private void AddFiles(StringBuilder builder, string path, string searchPattern)
        {
            foreach (string file in Directory.GetFiles(path, searchPattern))
            {
                IEnumerable<string> lines = File.ReadLines(file);
                CheckLines(file, lines);
                _totalLines += lines.Count();
                _ = builder.Append(
                    string.Format(FORMAT_STRING, file[(PATH.Length + 1)..], lines.Count()));
            }
        }


        /// <summary>
        /// Skip PlantUML files and HTML <pre> keyword.
        /// </summary>
        /// <param name="file"></param>
        /// <param name="lines"></param>
        private void CheckLines(string file, IEnumerable<string> lines)
        {
            if ((lines.Count() > 0) && !lines.ElementAt(0).StartsWith("@startuml"))
            {
                bool preKeywordActive = false;
                int lineNumber = 0;
                foreach (string line in lines)
                {
                    preKeywordActive = line.TrimStart().StartsWith("<pre ") ||
                        (line.Trim() != "</pre>" && preKeywordActive);

                    if (!preKeywordActive && (line.Length > 100))
                    {
                        _ = MessageBox.Show($"File {file}, line {lineNumber} is too long",
                            "Project", MessageBoxButton.OK, MessageBoxImage.Warning);
                    }
                    lineNumber++;
                }
            }
        }
    }
}