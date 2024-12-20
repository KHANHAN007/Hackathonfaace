#include <stdio.h>
#include <string.h>

struct Dish
{
    int id;
    char name[100];
    float price;
};
typedef struct Dish Dish;
void printMenu(Dish menu[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d. name: %s, price: %.2f\n", menu[i].id, menu[i].name, menu[i].price);
}
void addDish(Dish menu[], int *size, int pos)
{
    if (pos < 0 || pos > *size)
    {
        printf("Vi tri chen khong hop le.\n");
        return;
    }
    Dish newDish;
    newDish.id = *size + 1;
    printf("Nhap ten mon an: ");
    getchar();
    fgets(newDish.name, sizeof(newDish.name), stdin);
    newDish.name[strcspn(newDish.name, "\n")] = '\0';
    printf("Nhap gia mon an: ");
    scanf("%f", &newDish.price);
    for (int i = *size; i > pos; --i)
    {
        menu[i] = menu[i - 1];
    }
    menu[pos] = newDish;
    (*size)++;
}
void editDish(Dish menu[], int size, int pos)
{
    if (pos < 0 || pos >= size)
    {
        printf("Vi tri khong hop le.\n");
        return;
    }

    printf("Nhap ten mon an moi: ");
    getchar();
    fgets(menu[pos].name, sizeof(menu[pos].name), stdin);
    menu[pos].name[strcspn(menu[pos].name, "\n")] = '\0';

    printf("Nhap gia mon an moi: ");
    scanf("%f", &menu[pos].price);
}
void deleteDish(Dish menu[], int *size, int pos)
{
    if (pos < 0 || pos >= *size)
    {
        printf("Vi tri khong hop le.\n");
        return;
    }
    for (int i = pos; i < *size - 1; i++)
        menu[i] = menu[i + 1];

    (*size)--;
}
void sortDescending(Dish menu[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (menu[i].price < menu[j].price)
            {
                Dish temp = menu[i];
                menu[i] = menu[j];
                menu[j] = temp;
            }
        }
    }
}
void sortAscending(Dish menu[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (menu[i].price > menu[j].price)
            {
                Dish temp = menu[i];
                menu[i] = menu[j];
                menu[j] = temp;
            }
        }
    }
}
int linearSearch(Dish menu[], int size, char name[])
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(menu[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}
int binarySearch(Dish menu[], int size, char name[])
{
    int l = 0, r = size - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        int cmp = strcmp(menu[mid].name, name);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}
int main()
{
    Dish menu[100] = {
        {1, "Pho", 50.0},
        {2, "Banh Mi", 30.0},
        {3, "Banh Cun", 40.0},
        {4, "Goi cuon", 25.0},
        {5, "Bun rieu", 35.0}};
    int menuSize = 5;
    int choice, pos;
    char searchName[100];
    while (1)
    {
        printf("\n\t\tMENU:\n");
        printf("1. In ra gia tri cac phan tu trong menu\n");
        printf("2. Them mot phan tu vao vi tri chi dinh\n");
        printf("3. Sua mot phan tu o vi tri chi dinh\n");
        printf("4. Xoa mot phan tu o vi tri chi dinh\n");
        printf("5. Sap xep cac phan tu\n");
        printf("6. Tim kiem phan tu theo name\n");
        printf("7. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printMenu(menu, menuSize);
            break;
        case 2:
            printf("Nhap vi tri can chen (0 - %d): ", menuSize);
            scanf("%d", &pos);
            addDish(menu, &menuSize, pos);
            break;
        case 3:
            printf("Nhap vi tri can sua (0 - %d): ", menuSize - 1);
            scanf("%d", &pos);
            editDish(menu, menuSize, pos);
            break;
        case 4:
            printf("Nhap vi tri can xoa (0 - %d): ", menuSize - 1);
            scanf("%d", &pos);
            deleteDish(menu, &menuSize, pos);
            break;
        case 5:
            printf("Chon cach sap xep:\n");
            printf("a. Giam dan theo gia\n");
            printf("b. Tang dan theo gia\n");
            getchar();
            char sortChoice;
            scanf("%c", &sortChoice);
            if (sortChoice == 'a')
                sortDescending(menu, menuSize);
            else if (sortChoice == 'b')
                sortAscending(menu, menuSize);
            else
                printf("Lua chon khong hop le.\n");
            break;
        case 6:
            printf("Nhap ten mon an can tim: ");
            getchar();
            fgets(searchName, sizeof(searchName), stdin);
            searchName[strcspn(searchName, "\n")] = '\0';
            printf("Chon cach tim kiem:\n");
            printf("a. Tim kiem tuyen tinh\n");
            printf("b. Tim kiem nhi phan\n");
            char searchChoice;
            scanf("%c", &searchChoice);
            if (searchChoice == 'a')
            {
                int index = linearSearch(menu, menuSize, searchName);
                if (index != -1)
                    printf("Mon an tim duoc: ID: %d, Name: %s, Price: %.2f\n", menu[index].id, menu[index].name, menu[index].price);
                else
                    printf("Mon an khong ton tai.\n");
            }
            else if (searchChoice == 'b')
            {
                sortAscending(menu, menuSize);
                int index = binarySearch(menu, menuSize, searchName);
                if (index != -1)
                    printf("Mon an tim duoc: ID: %d, Name: %s, Price: %.2f\n", menu[index].id, menu[index].name, menu[index].price);
                else
                    printf("Mon an khong ton tai.\n");
            }
            else
                printf("Lua chon khong hop le.\n");
            break;
        case 7:
            printf("Thoat!\n");
            return 0;
        default:
            printf("Lua chon khong hop le. Chon lai\n");
        }
    }
}
