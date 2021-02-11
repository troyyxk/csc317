#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>, std::vector<std::pair<double, std::shared_ptr<Object>>>, std::greater<std::pair<double, std::shared_ptr<Object>>>> q;
  double d_r, d_s, d_l, cur_s;
  std::shared_ptr<Object> subtree, cur_des;
  bool flag = false;
  d_r = point_box_squared_distance(query, root->box);
  q.push(std::make_pair(d_r, root));
  // d
  sqrd = std::numeric_limits<double>::max(); 

  while (!q.empty())
  {
    d_s = q.top().first;
    subtree = q.top().second;
    q.pop();
    std::shared_ptr<AABBTree> ab_t = std::dynamic_pointer_cast<AABBTree>(subtree);
    if (d_s<sqrd){
      if (ab_t){
        if (ab_t->left) {
          d_l = point_box_squared_distance(query, ab_t->left->box);
          q.push(std::make_pair(d_l, ab_t->left));
        }
        if (ab_t->right) {
          d_r = point_box_squared_distance(query, ab_t->right->box);
          q.push(std::make_pair(d_r, ab_t->right));
        }
      }
      // leaf
      else{
        if(subtree->point_squared_distance(query, min_sqrd, max_sqrd, cur_s,cur_des) && (cur_s<sqrd)){
          flag = true;
          sqrd = cur_s;
          descendant = subtree;
        }
      }
    }
  }
  
  return flag;
  ////////////////////////////////////////////////////////////////////////////
}
