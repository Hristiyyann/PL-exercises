/*
 * Exercise 1:
 * - Да се дефинира базов клас за студент зададен с име, факултетен номер,
 *   номер на група и курс.
 * - Да се дефинира производен клас за успех зададен с динамичен масив от
 *   оценките по всички дисциплини до момента (дължината на масива зависи от
 *   курса – счита се, че за семестър броят на оценките е 5).
 * - Класовете да включват конструктори без параметри за попълване на
 *   член-променливите в диалог.
 * - Да се определят и извеждат средният успех за всеки студент и максималния
 *   среден успех за зададена група.
 * - Да се извежда пълната информация за всеки студент и за студент, зададен
 *   с факултетния си номер.
 * - Да се предефинира операцията <<, която да се използва за извеждане на
 *   данните.
 * - Данните да се съхраняват във файл.
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Student
{
protected:
    string name_;
    string faculty_number_;
    unsigned int group_number_;
    unsigned int course_;

public:
    Student()
    {
        cout << "Initializing student..." << endl;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name_);
        cout << "Enter faculty number: ";
        cin >> faculty_number_;
        cout << "Enter group number: ";
        cin >> group_number_;
        cout << "Enter course: ";
        cin >> course_;
    }

    Student(string name, string faculty_number, unsigned int group_number, unsigned int course)
        : name_(name), faculty_number_(faculty_number), group_number_(group_number), course_(course) {}

    string getFacultyNumber() const { return faculty_number_; }
    string getName() const { return name_; }
    unsigned int getGroup() const { return group_number_; }
    unsigned int getCourse() const { return course_; }

    string getInfo() const
    {
        stringstream ss;

        ss << "Name: " << name_ << endl;
        ss << "Faculty Number: " << faculty_number_ << endl;
        ss << "Group: " << group_number_ << endl;
        ss << "Course: " << course_;

        return ss.str();
    }
};

class Success : public Student
{
private:
    double *grades_;
    int grades_count_;

public:
    Success() : Student()
    {
        grades_count_ = course_ * 2 * 5;
        grades_ = new double[grades_count_];

        cout << "Enter " << grades_count_ << " grades:" << endl;
        for (int i = 0; i < grades_count_; i++)
        {
            cout << "Grade " << i + 1 << ": ";
            cin >> grades_[i];
        }
    }

    Success(string name, string fn, unsigned int group, unsigned int course,
            const vector<double> &gradesList)
        : Student(name, fn, group, course)
    {
        grades_count_ = gradesList.size();
        grades_ = new double[grades_count_];
        for (int i = 0; i < grades_count_; i++)
        {
            grades_[i] = gradesList[i];
        }
    }

    ~Success()
    {
        delete[] grades_;
    }

    double getAverageGrade() const
    {
        double sum = 0;
        for (int i = 0; i < grades_count_; i++)
        {
            sum += grades_[i];
        }
        return grades_count_ > 0 ? sum / grades_count_ : 0;
    }

    friend ostream &operator<<(ostream &out, const Success &s)
    {
        out << s.getInfo() << endl;
        out << "Average grade: " << s.getAverageGrade();
        return out;
    }
};

class SuccessManager
{
private:
    vector<Success> students;

public:
    void addStudent(const Success &s)
    {
        students.push_back(s);
    }

    double getMaxAverageForGroup(unsigned int group) const
    {
        double maxAverageGrade = 0;
        bool found = false;

        for (const Success &success : students)
        {
            if (success.getGroup() != group)
                continue;
            double averageGrade = success.getAverageGrade();
            if (averageGrade > maxAverageGrade)
            {
                maxAverageGrade = averageGrade;
                found = true;
            }
        }

        return found ? maxAverageGrade : -1;
    }

    void getStudentInfoByFacultyNumber(string faculty_number) const
    {
        for (const Success &success : students)
        {

            if (success.getFacultyNumber() == faculty_number)
            {
                cout << success.getInfo() << endl;
                return;
            }
        }
        cout << "No such student found" << endl;
    }
};

int main()
{
    SuccessManager manager;

    manager.addStudent(Success("Ivan Petrov", "1234567", 3, 2,
                               {5.50, 6.00, 4.75, 5.00, 5.25}));
    manager.addStudent(Success("Maria Ivanova", "1234568", 3, 2,
                               {5.25, 5.75, 6.00, 5.50, 5.00}));
    manager.addStudent(Success("Georgi Georgiev", "1234569", 4, 3,
                               {4.00, 4.50, 5.00, 4.75, 4.25}));

    cout << "Max average for group 3: "
         << manager.getMaxAverageForGroup(3) << endl;

    cout << "\nSearching for student 1234568:" << endl;
    manager.getStudentInfoByFacultyNumber("1234568");

    return 0;
}