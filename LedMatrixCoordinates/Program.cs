// See https://aka.ms/new-console-template for more information
Console.WriteLine("LED MATRIX ALTERNATING/REVERSEDROW COORDINATES CALCULATOR");

Console.Write("Rows   : ");
int rows = Convert.ToInt32(Console.ReadLine());
Console.Write("Columns: ");
int columns = Convert.ToInt32(Console.ReadLine());

Console.WriteLine("\n");
Console.WriteLine(string.Format("Total LEDs        : {0} leds", rows * columns));
Console.WriteLine(string.Format("Length (60 leds/m): {0:0.00} m", rows * columns / 60));
Console.WriteLine(string.Format("Area              : {0:0.00} x {1:0.00} cm", columns * 100.0 / 60, rows * 100.0 / 60));
Console.WriteLine(string.Format("Max Power         : {0:0.00} A", 60 * rows * columns / 1000));

Console.Write("     ");
for (int column = 0; column < columns; column++)
{
    Console.Write(string.Format("{0, 3} ", column));
}
Console.WriteLine();

Console.Write("     ");
for (int column = 0; column < columns; column++)
{
    Console.Write("----");
}
Console.WriteLine();

for (int row = 0; row < rows; row++)
{
    Console.Write(string.Format("{0, 3} |", row));
    for (int column = 0; column < columns; column++)
    {
        Console.Write(string.Format("{0, 3} ", row * columns + (row % 2 == 0 ? column : columns - column - 1)));
    }
    Console.WriteLine();
}
