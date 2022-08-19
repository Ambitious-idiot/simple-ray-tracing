#include "box.h"

Box::Box(const Point3& p0, const Point3& p1, const shared_ptr<Material>& ptr) {
    box_min = p0;
    box_max = p1;

    sides.append(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides.append(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
    sides.append(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides.append(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
    sides.append(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides.append(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}
