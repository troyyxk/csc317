#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // initialize list of candidate leaf pairs
  // leaf_pairs ← {}
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> Q;
  // if root_A.box intersects root_B.box
  //   Q.insert( root_A, root_B )
  if(box_box_intersect(rootA->box, rootB->box)){
    Q.push_back(std::make_pair(rootA, rootB));
  }

  std::shared_ptr<Object> node_A, node_B;
  // while Q not empty
  while(!Q.empty()){
  //   {nodeA,nodeB} ← Q.pop
    node_A = Q.back().first;
    node_B = Q.back().second;
    Q.pop_back();
  //   if nodeA and nodeB are leaves
  //     leaf_pairs.insert( node_A, node_B )
    std::shared_ptr<AABBTree> ta = std::dynamic_pointer_cast<AABBTree>(node_A);
    std::shared_ptr<AABBTree> tb = std::dynamic_pointer_cast<AABBTree>(node_B);
    if ((!ta) && (!tb)){
      leaf_pairs.push_back(std::make_pair(node_A, node_B));
    }
  //   else if node_A is a leaf
    else if (!ta){
      if (tb->left != NULL){
        if (box_box_intersect(node_A->box, tb->left->box)){
          Q.push_back(std::make_pair(node_A, tb->left));
        }
      }
      if (tb->right != NULL){
        if (box_box_intersect(node_A->box, tb->right->box)){
          Q.push_back(std::make_pair(node_A, tb->right));
        }
      }
    }
  //   else if node_B is a leaf
    else if (!tb){
      if (ta->left != NULL){
        if (box_box_intersect(node_B->box, ta->left->box)){
          Q.push_back(std::make_pair(ta->left, node_B));
        }
      }
      if (ta->right != NULL){
        if (box_box_intersect(node_B->box, ta->right->box)){
          Q.push_back(std::make_pair(ta->right, node_B));
        }
      }
    }
  //   else
    else{
      if (ta->left != NULL){
        if (tb->left != NULL){
          if (box_box_intersect(ta->left->box, tb->left->box)){
            Q.push_back(std::make_pair(ta->left, tb->left));
          }
        }
        if (tb->right != NULL){
          if (box_box_intersect(ta->left->box, tb->right->box)){
            Q.push_back(std::make_pair(ta->left, tb->right));
          }
        }
      }
      if (ta->right != NULL){
        if (tb->right != NULL){
          if (box_box_intersect(ta->right->box, tb->right->box)){
            Q.push_back(std::make_pair(ta->right, tb->right));
          }
        }
        if (tb->left != NULL){
          if (box_box_intersect(ta->right->box, tb->left->box)){
            Q.push_back(std::make_pair(ta->right, tb->left));
          }
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
