using System.Collections.Generic;
using System;
namespace Task2
{
    static public class testingClass
    {
        static public void testingFunction() {
            
            var group = new Group("K27");
            
            //read all students from students.txt file and add to studentList container
            var studentsList = new List<string>();
            string currentLine;
            var streamReader = new System.IO.StreamReader(Program.PathToFile);
            while ((currentLine = streamReader.ReadLine()) != null)
            {
                studentsList.Add(currentLine);
            }
            
            //place all students to group
            for (int i = 0; i < studentsList.Count; ++i)
            {
                var currentStudent = new GoodStudent(studentsList[i]);
                if (i % 3 == 0)
                {
                    currentStudent.Relax();
                }
                else if (i % 3 == 2)
                {
                    currentStudent.Study();
                }
                else if (i % 3 == 2)
                {
                    currentStudent.Write();
                }
                group.AddStudent(currentStudent);
            }
            
            group.GetFullInfo();
        }
    }
}