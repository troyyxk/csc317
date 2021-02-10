#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int child_depth = a_depth + 1;
  // left, right shared
  // std::shared_ptr<MyClass> A = std::make_shared<MyClass>();
  std::vector<std::shared_ptr<Object> > left_objects, right_objects;
  this->left = std::make_shared<AABBTree>(left_objects, child_depth);
  this->right = std::make_shared<AABBTree>(right_objects, child_depth);
  ////////////////////////////////////////////////////////////////////////////
}
