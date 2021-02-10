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
  
  // Construct a axis-aligned bounding box tree given a list of objects. Use the
  // midpoint along the longest axis of the box containing the given objects to
  // determine the left-right split.
  int num_objects = objects.size();
  int i, obj_id, axis_id;
  double cur_axis_length;
  double longest_axis_length = 0;
  bool first = true;

  // find object and the longest axis;
  for (i=0; i<num_objects; i++){
    insert_box_into_box(objects[i]->box, this->box);
  }
  Eigen::RowVector3d axis_lengths, mid_points;
  for (i=0; i<3; i++){
    cur_axis_length = this->box.max_corner[i] - this->box.min_corner[i];
    axis_lengths[i] = cur_axis_length;
    mid_points[i] = (cur_axis_length/2)+this->box.min_corner[i];
  }
  for (i=0; i<3; i++){
    if (first || (axis_lengths[i]>longest_axis_length)){
      first = false;
      longest_axis_length = axis_lengths[i];
      axis_id = i;
    }
  }

  double cur_axis_pos;
  for (i=0; i<num_objects; i++){
    cur_axis_pos = objects[i]->box.center()[axis_id];
    // smaller, to the left
    if (cur_axis_pos < mid_points[axis_id]){
      left_objects.push_back(objects[i]);
    }
    // bigger, to the right
    else{
      right_objects.push_back(objects[i]);
    }
  }

  // no element
  if  ((left_objects.size() == 0) && (right_objects.size() == 0)){
    this->left = NULL;
    this->right = NULL;
  }
  else if (left_objects.size() == 0)
  {
    this->left = NULL;
    this->right = std::make_shared<AABBTree>(right_objects, child_depth);
  }
  else if (right_objects.size() == 0)
  {
    this->left = std::make_shared<AABBTree>(left_objects, child_depth);
    this->right = NULL;
  }
  else{
    this->left = std::make_shared<AABBTree>(left_objects, child_depth);
    this->right = std::make_shared<AABBTree>(right_objects, child_depth);
  }
  ////////////////////////////////////////////////////////////////////////////
}
