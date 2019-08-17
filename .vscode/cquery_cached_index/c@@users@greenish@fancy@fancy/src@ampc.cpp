#include "AMPC.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include <numeric>

namespace okapi {

  //const TimeUtil &itimeUtil = TimeUtilFactory::create()
  AMPC::AMPC(const TimeUtil &itimeUtil,
  const double imaxVel,
  const double imaxAccel,
  const double imaxJerk,
  const std::shared_ptr<ChassisModel> &imodel,
  const ChassisScales &iscales,
  AbstractMotor::GearsetRatioPair ipair)
  : AsyncMotionProfileController(
    itimeUtil,
    imaxVel,
    imaxAccel,
    imaxJerk,
    imodel,
    iscales,
    ipair) {

    }

  void AMPC::executeSinglePath(const TrajectoryPair &path, std::unique_ptr<AbstractRate> rate) {
    const auto reversed = direction.load(std::memory_order_acquire);

    for (int i = 0; i < path.length && !isDisabled(); ++i) {
      const auto leftRPM = convertLinearToRotational(path.left[i].velocity * mps).convert(rpm);
      const auto rightRPM = convertLinearToRotational(path.right[i].velocity * mps).convert(rpm);

      model->left(leftRPM / toUnderlyingType(pair.internalGearset) * reversed);
      model->right(rightRPM / toUnderlyingType(pair.internalGearset) * reversed);

      rate->delayUntil(1_ms);
    }
  }

}
