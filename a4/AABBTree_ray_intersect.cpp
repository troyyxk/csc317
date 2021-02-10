#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit = false;
  t = std::numeric_limits<double>::max();
  if (!ray_intersect_box(ray, this->box, min_t, max_t)) {
    return hit;
  }
  hit = true;
  
  std::shared_ptr<Object> ld, rd;
  ld = this->left;
  rd = this->right;
  double lt, rt;
  lt = std::numeric_limits<double>::max();
  rt = std::numeric_limits<double>::max();
  bool lhit = false;
  bool rhit = false;
  if (this->left != NULL){
    lhit = this->left->ray_intersect(ray, min_t, max_t, lt, ld);
  }
  if (this->right != NULL){
    rhit = this->right->ray_intersect(ray, min_t, max_t, rt, rd);
  }

  // no hits, should not happen
  if ((!lhit) && (!rhit)){
    return false;
  }

  if (lhit){
    t = lt;
    descendant = ld;
  }

  if(rhit){
    t = rt;
    descendant = rd;
    if (lhit && (lt<rt)){
      t = lt;
      descendant = ld;
    }
  }


  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

