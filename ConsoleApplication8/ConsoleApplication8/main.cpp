#include "project.h"

int main() {
    ListCourses LC;
    InitList(LC);

    ListCourses List_Courses_SV;
    InitList(List_Courses_SV);

    ListNamHoc LNH = { NULL };
    NamHoc* N = NULL;
    Semester* sm = NULL;
    ListUser* LUR = addListUser("User.csv");

    char username[128] = "\0";
    char password[128] = "\0";
    bool checkstaff = false;

    bool mouseOnText = false;
    bool usernameBoxActive = false;
    bool passwordBoxActive = false;
    bool loginAttempted = false;
    bool loginSuccessful = false;
    bool showError = false;

    if (Login(LUR, username, password, checkstaff) && checkstaff) {
        const int dashboardWidth = 1366;
        const int dashboardHeight = 768;
        SetWindowSize(dashboardWidth, dashboardHeight);
        SetWindowTitle("staff dashboard");
        SetTargetFPS(60);

        Rectangle buttons[6];
        const char* buttonLabels[6] = {
            "Create New School Year",
            "Create New Semester",
            "Add Course",
            "View Course",
            "Add Student to Course and View",
            "Change password"
        };

        bool createNewSchoolYearActive = false;
        char schoolYearInput[128] = "\0";
        Rectangle schoolYearInputBox = { dashboardWidth / 2 - 100, 450, 200, 40 };
        bool schoolYearInputBoxActive = false;

        bool createNewSemesterActive = false;

        bool createNewCourseActive = false;

        bool ViewCourseActive = false;

        char ViewCourseInput[128] = "\0";
        bool ViewCourseInputBoxActive = false;

        bool AddsvInputBoxActive = false;
        char AddsvInput[128] = "\0";
        Rectangle AddsvInputBox = { dashboardWidth / 2 - 100, 450, 200, 40 };

        bool ChangepasswordActive = false;

        for (int i = 0; i < 6; i++) {
            buttons[i].x = (dashboardWidth - 400) / 2;
            buttons[i].y = 50 + i * 60;
            buttons[i].width = 400;
            buttons[i].height = 40;
        }

        while (!WindowShouldClose()) {
            Vector2 mousePoint = GetMousePosition();
            bool mouseOverButton[6] = { false };

            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 6; i++) {
                mouseOverButton[i] = CheckCollisionPointRec(mousePoint, buttons[i]);
                DrawButton(buttons[i], buttonLabels[i], mouseOverButton[i]);

                if (mouseOverButton[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    // Reset all active states
                    createNewSchoolYearActive = false;
                    schoolYearInputBoxActive = false;
                    createNewSemesterActive = false;
                    createNewCourseActive = false;
                    ViewCourseActive = false;
                    ViewCourseInputBoxActive = false;
                    AddsvInputBoxActive = false;
                    ChangepasswordActive = false;

                    switch (i) {
                    case 0:
                        createNewSchoolYearActive = true;
                        break;
                    case 1:
                        createNewSemesterActive = true;
                        break;
                    case 2:
                        createNewCourseActive = true;
                        break;
                    case 3:
                        ViewCourseActive = true;
                        break;
                    case 4:
                        AddsvInputBoxActive = true;
                        break;
                    case 5:
                        ChangepasswordActive = true;
                        break;
                    }
                }
            }

            if (createNewSchoolYearActive) {
                CreateNewSchoolYeabutton(createNewSchoolYearActive, schoolYearInputBoxActive, schoolYearInput, LNH, N, mousePoint);
            }

            if (createNewSemesterActive) {
                // Implementation for creating new semester
                taohocky(sm, LNH);
                createNewSemesterActive = false;
            }

            if (createNewCourseActive) {
                CloseWindow();
                CourseDashboard(dashboardWidth, dashboardHeight, LC);
                createNewCourseActive = false;
            }

            if (ViewCourseActive) {
                // Count the number of courses in the linked list
                int numRows = 0;
                Course* tempCount = LC.head;

                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                // Allocate memory for an array to store courses
                Course* courseArray = new Course[numRows];

                // Copy courses from linked list to array
                Course* temp = LC.head;
                Course* pretemp = NULL;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;  // Copy each course object
                    temp = temp->next;
                }
                // Draw the course table
                viewcourse(LC, courseArray, numRows);

                // Clean up dynamically allocated memory
                delete[] courseArray;

                ViewCourseActive = false;
            }

            if (AddsvInputBoxActive) {
                AddStudentsbutton(AddsvInput, AddsvInputBox, AddsvInputBoxActive, LC, dashboardWidth, dashboardHeight);
            }

            if (ChangepasswordActive) {
                // Implementation for changing password
                ChangePassword(LUR, username, password);
                saveListUser(LUR, "User.csv");
                ChangepasswordActive = false;
            }

            EndDrawing();
        }
    }
    else {
        const int dashboardWidth = 1366;
        const int dashboardHeight = 768;
        SetWindowSize(dashboardWidth, dashboardHeight);
        SetWindowTitle("user dashboard");
        SetTargetFPS(60);

        Rectangle buttons[4];
        const char* buttonLabels[4] = {
            "Profile",
            "Change Password",
            "Sign a course",
            "View courses"
        };

        bool viewprofileActive = false;
        bool ChangepasswordActive = false;
        bool dangkicourse = false;
        bool ViewCoursesActive = false;
        for (int i = 0; i < 4; i++) {
            buttons[i].x = (dashboardWidth - 400) / 2;
            buttons[i].y = 50 + i * 60;
            buttons[i].width = 400;
            buttons[i].height = 40;
        }

        while (!WindowShouldClose()) {
            Vector2 mousePoint = GetMousePosition();
            bool mouseOverButton[4] = { false };

            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 4; i++) {
                mouseOverButton[i] = CheckCollisionPointRec(mousePoint, buttons[i]);
                DrawButton(buttons[i], buttonLabels[i], mouseOverButton[i]);

                if (mouseOverButton[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    // Reset all active states
                    viewprofileActive = false;
                    ChangepasswordActive = false;

                    switch (i)
                    {
                    case 0:
                        viewprofileActive = true;
                        break;
                    case 1:
                        ChangepasswordActive = true;
                        break;
                    case 2:
                        dangkicourse = true;
                        break;
                    case 3:
                        ViewCoursesActive = true;
                        break;
                    }
                }
            }

            if (ChangepasswordActive) {
                // Implementation for changing password
                ChangePassword(LUR, username, password);
                saveListUser(LUR, "User.csv");
                ChangepasswordActive = false;
            }

            if (viewprofileActive) {
                User* user = timnodeuser(LUR, username, password);
                DisplayProfileInfo(user);
                viewprofileActive = false;
            }

            if (dangkicourse) {
                ImportCourseFile(LC, "Courses.csv");
                // Count the number of courses in the linked list
                int numRows = 0;
                Course* tempCount = LC.head;

                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                // Allocate memory for an array to store courses
                Course* courseArray = new Course[numRows];

                // Copy courses from linked list to array
                Course* temp = LC.head;
                Course* pretemp = NULL;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;  // Copy each course object
                    temp = temp->next;
                }
                // Draw the course table
                ViewSignCourses(LC, courseArray, numRows,List_Courses_SV);

                // Clean up dynamically allocated memory
                delete[] courseArray;

                dangkicourse = false;
            }

            if (ViewCoursesActive) {
                int numRows = 0;
                Course* tempCount = List_Courses_SV.head;
                // dem sl dong
                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                // Allocate memory for an array to store courses
                Course* courseArray = new Course[numRows];

                // Copy courses from linked list to array
                Course* temp = List_Courses_SV.head;
                Course* pretemp = NULL;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;  // Copy each course object
                    temp = temp->next;
                }
                // Draw the course table
                ViewCourses_SV(List_Courses_SV,courseArray,numRows);

                // Clean up dynamically allocated memory
                delete[] courseArray;

                ViewCoursesActive = false;
            }
    
            EndDrawing();
        }
    }    
    CloseWindow();
    return 0;
}
