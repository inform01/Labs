using System;
namespace Task3
{
    public class testingClassConverter
    {
        static public void testingFunctionConverter()
        {
            {
            
                Console.WriteLine("START TESTING CONVERTER");
                double dollarRate, eurosRate;
            
            
                Console.WriteLine("Please enter the dollar exchange rate in Ukraine");
                dollarRate = Convert.ToDouble(Console.ReadLine());
            
                Console.WriteLine("Please enter the euros exchange rate in Ukraine");
                eurosRate = Convert.ToDouble(Console.ReadLine());
            
                var converter = new Converter(dollarRate, eurosRate);
            
                Console.WriteLine("Please, enter the number you want convert to dollars or euros");
                double grivnas = Convert.ToDouble(Console.ReadLine());
            
            
                Console.WriteLine("Now, please, enter 'd' symbol to convert " + grivnas + " to dollars " +
                                  "and 'e' symbol to convert " + grivnas + " to euros:)");

                char operation = Convert.ToChar(Console.ReadLine());
                double result;
                if (operation == 'd')
                {
                    Console.WriteLine(grivnas + " grivnas is " + converter.ConvertToDollars(grivnas) + " dollars:)");
                }
            
                else if (operation == 'e')
                {
                    Console.WriteLine(grivnas + " grivnas is " + converter.ConvertToEuros(grivnas) + " euros:)");
                }
            }
        }
    }
}
