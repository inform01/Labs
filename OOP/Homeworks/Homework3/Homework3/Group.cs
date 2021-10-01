using System;
using System.Collections.Generic;

namespace Task2
{
    class Group
    {
        private string groupName;
        private List<Student> studentsList;


        public Group(List<Student> students)
        {
            studentsList = new List<Student>(students);
        }

        public Group(string groupName)
        {
            studentsList = new List<Student>();
            this.groupName = groupName;
        }

        public void AddStudent(Student student)
        {
            studentsList.Add(student);
        }

        public void GetInfo()
        {
            Console.WriteLine("Name of the group: " + groupName);
            for (int i = 0; i < studentsList.Count; ++i)
            {
                Console.WriteLine(i + 1 + "." + studentsList[i].getName());
            }
        }

        public void GetFullInfo()
        {
            Console.WriteLine("Name of the group: " + groupName);
            for (int i = 0; i < studentsList.Count; ++i)
            {
                Console.WriteLine(i + 1 + "." + studentsList[i].getName());
                Console.WriteLine("States of student number " + (i + 1) + ":");
                Console.WriteLine(studentsList[i].getStates());

            }
        }
    }
}