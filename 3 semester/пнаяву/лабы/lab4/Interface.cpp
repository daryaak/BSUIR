//#include "Interface.h"
//#include "Man.h"
//#include "MemberOfOrg.h"
//#include "Professor.h"
//#include "ProfMember.h"
//#include"MyQueue.cpp"
//
//void Interface::menu_pick_class() 
//{
//    int Type;
//    cout << "Введите: " << endl << "1. Человек" << endl << "2. Профессор" << endl
//        << "3. Член Организации" << endl << "4. Профессор-член" << endl;
//    cin >> Type;
//    cout << endl;
//    switch (Type)
//    {
//    case 1:
//    {
//        MyQueue<Man> People;
//        People.menu();
//        break;
//    }
//    case 2:
//    {
//        MyQueue<Professor> Professors;
//        Professors.menu();
//        break;
//    }
//    case 3:
//    {
//        MyQueue<MemberOfOrg> Members;
//        Members.menu();
//        break;
//    }
//    case 4:
//    {
//        MyQueue<ProfMember> ProfMembers;
//        ProfMembers.menu();
//        break;
//    }
//    default:
//    {
//        exit(1);
//    }
//    }
//};