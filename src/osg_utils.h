#pragma once

#include <iostream>
#include <osg/Vec3>

namespace osg_util {
std::ostream& operator<<(std::ostream& os, const osg::Vec3& v) {
  return os << v.x() << ", " << v.y() << ", " << v.z();
}

struct FaceCollector {
  void operator()(const osg::Vec3& v1, const osg::Vec3& v2,
                  const osg::Vec3& v3) {
    std::cout << "Face vertices: (" << v1 << "); (" << v2 << "); (" << v3 << ")"
              << std::endl;
  }
};
}  // namespace osg_util