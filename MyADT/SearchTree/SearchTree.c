//
// Created by Kokomi on 2022/11/24.
//
#include <stdio.h>
#include <stdlib.h>
#include "SearchTree.h"

static int compare(Item item1, Item item2);
static void copy(Item *dest, Item *source);
SearchTree MakeEmpty(SearchTree T) {
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

Position Find(Item item, SearchTree T) {
    if (T == NULL)
        return NULL;
    if (compare(item, T->item) > 0)
        return Find(item, T->right);
    else if (compare(item, T->item) < 0)
        return Find(item, T->left);
    else
        return T;
}

Position FindMin(SearchTree T) {
    if (T == NULL)
        return NULL;
    if (T->left == NULL)
        return T;
    else FindMin(T->left);
}

Position FindMax(SearchTree T) {
    if (T == NULL)
        return NULL;
    if (T->right == NULL)
        return T;
    else FindMax(T->right);
}

SearchTree Insert(Item item, SearchTree T) {
    /*如果是空树*/
    if (T == NULL) {
        T = (struct TreeNode*) malloc(sizeof(struct TreeNode));
        if (T == NULL) {
            fprintf(stderr, "Out of space!\n");
            exit(EXIT_FAILURE);
        } else {
            copy(&T->item, &item);
            T->right = T->left = NULL;
        }
    }
    else if (compare(item, T->item) > 0)
        T->right = Insert(item, T->right);
    else if (compare(item, T->item) < 0)
        T->left = Insert(item, T->left);
    /*其他情况item已经在树中，不做任何事*/
    return T;
}

SearchTree Delete(Item item, SearchTree T) {
    Position TmpCell;
    if (T == NULL) {
        fprintf(stderr, "Not found!\n");
        exit(EXIT_FAILURE);
    } //defined as NULL
    else if (compare(item, T->item) > 0)
        T->right = Delete(item, T->right);
    else if (compare(item, T->item) < 0)
        T->left = Delete(item, T->left);
    /*其他情况只有找到item，下面把它删除*/
    else if (T->left && T->right) {//两个孩子
        TmpCell = FindMin(T->right);
        copy(&T->item, &TmpCell->item);
        T->right = Delete(T->item, T->right);
    } else { //一个孩子
        TmpCell = T;
        if (T->right == NULL) { //包括了没有孩子的情况
            T = T->left;
        } else if (T->left == NULL) {
            T = T->right;
        }
        free(TmpCell);
    }
    return T;
}

Item Retrieve(Position position) {
    return position->item;
}

void traverse(SearchTree T, void (*fp)(Item item)) {
    if (T) {
        (*fp)(T->item);
        traverse(T->left, fp);
        traverse(T->right, fp);
    } else {
        return;
    }
}

static int compare(Item item1, Item item2) {
    return item1.num - item2.num;
}
static void copy(Item *dest, Item *source) {
    dest->num = source->num;
}
