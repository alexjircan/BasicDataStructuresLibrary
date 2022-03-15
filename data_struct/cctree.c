#include "cctree.h"
#include "common.h"
#include "string.h"
#include "stdio.h"

int TreeCreate(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    if (0 != TreeDestroy(Tree))
    {
        return -1;
    }

    CC_TREE* tree = *Tree;

    tree = (CC_TREE*)malloc(sizeof(CC_TREE));

    if (NULL == tree)
    {
        return -1;
    }

    memset(tree, 0, sizeof(*tree));

    tree->Count = 0;
    tree->Root = NULL;

    *Tree = tree;

    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    CC_TREE* tree = *Tree;


    if (NULL != tree && NULL != tree->Root) {
        TreeClear(*Tree);
    }

    free(tree);

    *Tree = NULL;

    return 0;
}

int TreeCreateNode(CC_NODE** Node, int Value)
{
    if (NULL == Node)
    {
        return -1;
    }

    CC_NODE* node = *Node;

    node = (CC_NODE*)malloc(sizeof(CC_NODE));

    if (NULL == node)
    {
        return -1;
    }

    node->Value = Value;
    node->Height = 0;
    node->Left = NULL;
    node->Right = NULL;

    *Node = node;

    return 0;
}

void TreePPrintUtil(CC_NODE* Node, int Level)
{
    if (NULL == Node)
    {
        return;
    }

    TreePPrintUtil(Node->Right, Level + 1);

    for (int i = 0; i < Level; i++)
    {
        printf("   ");
    }
    printf("%d\n", Node->Value);

    TreePPrintUtil(Node->Left, Level + 1);
}

int TreePPrint(CC_TREE* Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }

    if (0 == TreeGetCount(Tree))
    {
        printf("(empty)\n");
        return 0;
    }

    TreePPrintUtil(Tree->Root, 0);

    return 0;
}

int MaxUtil(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int TreeGetNodeHeight(CC_NODE* Node)
{
    if (NULL == Node)
    {
        return -1;
    }

    return 1 + MaxUtil(TreeGetNodeHeight(Node->Left), TreeGetNodeHeight(Node->Right));
}

void TreeRightRotate(CC_NODE** NodeY)
{
    CC_NODE* NodeX = (* NodeY)->Left;
    CC_NODE* NodeT2 = NodeX->Right;

    NodeX->Right = *NodeY;
    (*NodeY)->Left = NodeT2;

    (*NodeY)->Height = TreeGetNodeHeight(*NodeY);
    NodeX->Height = TreeGetNodeHeight(NodeX);

    (*NodeY) = NodeX;
}

void TreeLeftRotate(CC_NODE** NodeX)
{
    CC_NODE* NodeY = (*NodeX)->Right;
    CC_NODE* NodeT2 = NodeY->Left;

    NodeY->Left = *NodeX;
    (*NodeX)->Right = NodeT2;

    (*NodeX)->Height = TreeGetNodeHeight(*NodeX);
    NodeY->Height = TreeGetNodeHeight(NodeY);

    (*NodeX) = NodeY;
}

int NodeGetBalanceFactor(CC_NODE* Node)
{
    if (NULL == Node)
    {
        return 0;
    }

    return TreeGetNodeHeight(Node->Left) - TreeGetNodeHeight(Node->Right);
}

int TreeInsertRec(CC_NODE** Node, int Value)
{
    if (NULL == Node)
    {
        return -1;
    }

    if (NULL == *Node)
    {
        if (0 != TreeCreateNode(Node, Value))
        {
            return -1;
        }
        return 0;
    }

    if (Value <= (*Node)->Value)
    {
        if (0 != TreeInsertRec(&((*Node)->Left), Value))
        {
            return -1;
        }
    }
    else
    {
        if (0 != TreeInsertRec(&((*Node)->Right), Value))
        {
            return -1;
        }
    }

    (*Node)->Height = TreeGetNodeHeight(*Node);

    int balanceFactor = NodeGetBalanceFactor(*Node);

    if (balanceFactor > 1 && Value < (*Node)->Left->Value)
    {
        TreeRightRotate(Node);
    }
    else if (balanceFactor < -1 && Value >(*Node)->Right->Value)
    {
        TreeLeftRotate(Node);
    }
    else if (balanceFactor > 1 && Value > (*Node)->Left->Value)
    {
        TreeLeftRotate(&((*Node)->Left));
        TreeRightRotate(Node);
    }
    else if (balanceFactor < -1 && Value < (*Node)->Right->Value)
    {
        TreeRightRotate(&((*Node)->Right));
        TreeLeftRotate(Node);
    }

    return 0;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    CC_NODE* currentNode = Tree->Root;

    if (0 != TreeInsertRec(&currentNode, Value))
    {
        return -1;
    }

    Tree->Root = currentNode;
    Tree->Count++;

    return 0;
}

CC_NODE* TreeMinValueNode(CC_NODE* Node)
{
    CC_NODE* currentNode = Node;

    while (NULL != currentNode->Left)
    {
        currentNode = currentNode->Left;
    }

    return currentNode;
}

int TreeRemoveRec(CC_NODE** Node, int Value)
{
    if (NULL == Node)
    {
        return -1;
    }

    if (NULL == *Node)
    {
        return 0;
    }

    if (Value < (*Node)->Value)
    {
        if (0 != TreeRemoveRec(&((*Node)->Left), Value))
        {
            return -1;
        }
    }
    else if (Value > (*Node)->Value)
    {
        if (0 != TreeRemoveRec(&((*Node)->Right), Value))
        {
            return -1;
        }
    }
    else
    {
        if (NULL == (*Node)->Left || NULL == (*Node)->Right)
        {
            CC_NODE* temp = (NULL != (*Node)->Left) ? (*Node)->Left : (*Node)->Right;

            if (NULL == temp)
            {
                temp = (*Node);
                *Node = NULL;
            }
            else
            {
                **Node = *temp;
            }

            free(temp);
        }
        else
        {
            CC_NODE* temp = TreeMinValueNode((*Node)->Right);

            (*Node)->Value = temp->Value;

            if (0 != TreeRemoveRec(&((*Node)->Right), temp->Value))
            {
                return -1;
            }
        }
    }

    if (NULL == (*Node))
    {
        return 0;
    }

    (*Node)->Height = 1 + MaxUtil(TreeGetNodeHeight((*Node)->Left), TreeGetNodeHeight((*Node)->Right));

    int balanceFactor = NodeGetBalanceFactor(*Node);

    if (balanceFactor > 1 && NodeGetBalanceFactor((*Node)->Left) >= 0)
    {
        TreeRightRotate(Node);
        return 0;
    }

    if (balanceFactor > 1 && NodeGetBalanceFactor((*Node)->Left) < 0)
    {
        TreeLeftRotate(&((*Node)->Left));
        TreeRightRotate(Node);
        return 0;
    }

    if (balanceFactor < -1 && NodeGetBalanceFactor((*Node)->Right) <= 0)
    {
        TreeLeftRotate(Node);
        return 0;
    }

    if (balanceFactor < -1 && NodeGetBalanceFactor((*Node)->Right) > 0)
    {
        TreeRightRotate(&((*Node)->Right));
        TreeLeftRotate(Node);
        return 0;
    }

    return 0;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    CC_NODE* currentNode = Tree->Root;

    if (1 != TreeContains(Tree, Value))
    {
        return -1;
    }

    while (1 == TreeContains(Tree, Value)) {
        if (0 != TreeRemoveRec(&currentNode, Value))
        {
            return -1;
        }
        Tree->Count--;
    }
    Tree->Root = currentNode;
    return 0;
}

int TreeContainsRec(CC_NODE* Current, int Value)
{
    if (NULL == Current)
    {
        return 0;
    }
    if (Value == Current->Value)
    {
        return 1;
    }

    return TreeContainsRec(Current->Left, Value) || TreeContainsRec(Current->Right, Value);
}

int TreeContains(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    return TreeContainsRec(Tree->Root, Value);
}

int TreeGetCount(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    return Tree->Count;
}

int TreeGetHeight(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    if (NULL == Tree->Root)
    {
        return 0;
    }

    return Tree->Root->Height;
}

void TreeClearRec(CC_NODE** Node)
{
    if (NULL != (*Node)->Left)
    {
        TreeClearRec(&((*Node)->Left));
    }
    if (NULL != (*Node)->Right)
    {
        TreeClearRec(&((*Node)->Right));
    }

    free(*Node);
    *Node = NULL;
}

int TreeClear(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    TreeClearRec(&(Tree->Root));
    Tree->Count = 0;

    return 0;
}

void TreePreorderUtil(CC_NODE* Node, int Index, int* Value, int* Count)
{
    if (NULL == Node)
    {
        return;
    }

    if (*Count <= Index)
    {
        if ((*Count) == Index)
        {
            *Value = Node->Value;
        }

        (*Count)++;

        TreePreorderUtil(Node->Left, Index, Value, Count);
        TreePreorderUtil(Node->Right, Index, Value, Count);
    }
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    int count = 0;
    TreePreorderUtil(Tree->Root, Index, Value, &count);

    return 0;
}

void TreeInorderUtil(CC_NODE* Node, int Index, int* Value, int* Count)
{
    if (NULL == Node)
    {
        return;
    }

    if (*Count <= Index)
    {

        TreeInorderUtil(Node->Left, Index, Value, Count);

        if ((*Count) == Index)
        {
            *Value = Node->Value;
        }

        (*Count)++;

        TreeInorderUtil(Node->Right, Index, Value, Count);
    }
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    int count = 0;
    TreeInorderUtil(Tree->Root, Index, Value, &count);

    return 0;
}

void TreePostorderUtil(CC_NODE* Node, int Index, int* Value, int* Count)
{
    if (NULL == Node)
    {
        return;
    }

    if (*Count <= Index)
    {

        TreePostorderUtil(Node->Left, Index, Value, Count);
        TreePostorderUtil(Node->Right, Index, Value, Count);

        if ((*Count) == Index)
        {
            *Value = Node->Value;
        }

        (*Count)++;
    }
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    if (NULL == Tree)
    {
        return -1;
    }

    int count = 0;
    TreePostorderUtil(Tree->Root, Index, Value, &count);

    return 0;
}

