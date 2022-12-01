//#ifndef AVLTREE_CPP_MERGE_H
//#define AVLTREE_CPP_MERGE_H
//
//#include "Player.h"
//
//
//{
//    if (array1 == nullptr || array2 == nullptr || size1 < 1 || size2 < 1)
//    {
//        return nullptr;
//    }
//    int i=0, j=0, k=0, t=0;
//    Player** united_array = new Player*[size1 + size2];
//    for (t=0; t<(size1+size2); t++)
//    {
//        united_array[t] = nullptr;
//    }
//    while (i < size1 && j < size2)
//    {
//        if (cond(array1[i], array2[j]) == Comparison::LESS_THAN)
//        {
//            united_array[k++] = array1[i++];
//        }
//        else
//        {
//            united_array[k++] = array2[j++];
//        }
//    }
//    while (i < size1)
//    {
//        united_array[k++] = array1[i++];
//    }
//    while (j < size2)
//    {
//        united_array[k++] = array2[j++];
//    }
//    return united_array;
//}
//
//#endif //AVLTREE_CPP_MERGE_H