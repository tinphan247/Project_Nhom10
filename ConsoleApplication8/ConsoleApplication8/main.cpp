#include "function.h"

int main() {
    ListCourses* LC=new ListCourses;
    InitList(LC);
    ListNamHoc LNH = { NULL };
    NamHoc* N = NULL;
    Semester* sm = NULL;
    ListUser* LUR = addListUser("User.csv");
    Semester* s = new Semester;
    ListCourses* List_Courses_SV=new ListCourses;
    InitList(List_Courses_SV);
    char username[128] = "\0";
    char password[128] = "\0";
    bool checkstaff = false;

    bool mouseOnText = false;
    bool usernameBoxActive = false;
    bool passwordBoxActive = false;
    bool loginAttempted = false;
    bool loginSuccessful = false;
    bool showError = false;
    bool showInvalidYearError = false;
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
            "View and Delete Course",
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
        bool showsemester = false;
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
                    case 3:
                    case 4:
                        if (LNH.phead == NULL || LNH.phead->Hocky == NULL) {
                            showError = true;
                        }
                        else {
                            if (i == 2) createNewCourseActive = true;
                            if (i == 3) ViewCourseActive = true;
                            if (i == 4) AddsvInputBoxActive = true;
                        }
                        break;
                    case 5:
                        ChangepasswordActive = true;
                        break;
                    }
                }
            }

            if (createNewSchoolYearActive) {
                CreateNewSchoolYeabutton(createNewSchoolYearActive, schoolYearInputBoxActive, schoolYearInput, LNH, N, mousePoint, showInvalidYearError);
            }

            if (createNewSemesterActive) {
                s = taohocky(sm, LNH);
                if (s->showsemester) {
                    showsemester = true;
                }
                createNewSemesterActive = false;
            }

            if (showsemester) {
                string hocKyText = "Hoc Ky " + to_string(s->thutu) + " -"+s->namhoc;
                const char* hocKyChar = hocKyText.c_str();
                int hocKyWidth = MeasureText(hocKyChar, 20);
                int hocKyX = 10;  
                int hocKyY = 10; 
                DrawText(hocKyChar, hocKyX, hocKyY, 20, DARKGRAY);
            }

            if (createNewCourseActive) {
                CloseWindow();
                CourseDashboard(dashboardWidth, dashboardHeight, s->lc);
                createNewCourseActive = false;
            }

            if (ViewCourseActive) {
                int numRows = 0;
                Course* tempCount = s->lc->head;

                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                Course* courseArray = new Course[numRows];

                Course* temp =s->lc->head;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;
                    temp = temp->next;
                }

                viewcourse(s->lc, courseArray, numRows);
                delete[] courseArray;

                ViewCourseActive = false;
            }

            if (AddsvInputBoxActive) {
                AddStudentsbutton(AddsvInput, AddsvInputBox, AddsvInputBoxActive, s->lc, dashboardWidth, dashboardHeight);
            }

            if (ChangepasswordActive) {
                ChangePassword(LUR, username, password);
                saveListUser(LUR, "User.csv");
                ChangepasswordActive = false;
            }

            if (showError) {
                DrawText("Error: No semester created yet!", 10, 10, 20, RED);
                if (showsemester)
                {
                    showError = false;
                }
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
                Course* tempCount = LC->head;

                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                // Allocate memory for an array to store courses
                Course* courseArray = new Course[numRows];

                // Copy courses from linked list to array
                Course* temp = LC->head;
                Course* pretemp = NULL;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;  // Copy each course object
                    temp = temp->next;
                }
                // Draw the course table
                ViewSignCourses(LC, courseArray, numRows, List_Courses_SV);

                // Clean up dynamically allocated memory
                delete[] courseArray;

                dangkicourse = false;
            }

            if (ViewCoursesActive) {
                int numRows = 0;
                Course* tempCount = List_Courses_SV->head;
                // dem sl dong
                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                // Allocate memory for an array to store courses
                Course* courseArray = new Course[numRows];

                // Copy courses from linked list to array
                Course* temp = List_Courses_SV->head;
                Course* pretemp = NULL;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;  // Copy each course object
                    temp = temp->next;
                }
                // Draw the course table
                ViewCourses_SV(List_Courses_SV, courseArray, numRows);

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
