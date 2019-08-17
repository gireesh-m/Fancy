#ifndef _AMPC_H_
#define _AMPC_H_

#include "okapi/api/control/async/asyncMotionProfileController.hpp"




namespace okapi {

class AMPC : public AsyncMotionProfileController {
  public:
  AMPC(
  const TimeUtil &itimeUtil,
  const double imaxVel,
  const double imaxAccel,
  const double imaxJerk,
  const std::shared_ptr<ChassisModel> &imodel,
  const ChassisScales &iscales,
  AbstractMotor::GearsetRatioPair ipair);

  void executeSinglePath(const TrajectoryPair &path, std::unique_ptr<AbstractRate> rate);

};
}
#endif
