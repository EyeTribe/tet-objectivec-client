# Change Log #
---

0.9.77 (2016-05-18)
---
- Removed heartbeats as the server no longer requires them
- Removed connection pull mode as the server natively only support push mode
- Changed connection methods (no more pulls)
- Changed verbose mechanism in GazeAPI constructor from bool (turn on/off) to integer (verbose level)
- Added missing remove_observer method
- Fixed issue with changed tracker state
- Fixed deadlock issues from blocking server calls
- Fixed Boost json concurrency crash bug
- Various code cleanup

0.9.49 (2014-12-10)
---
- Fixed a crash (exception) that sometimes would occur when disconnecting from the GazeAPI
- Fixed GazeAPI hanging when calling connect for the second time
- Added IConnectionStateListener to the GazerApi to be notified about connection state changes
- Added a missing calibration changed notification from the ICalibrationResultListener

0.9.36 (2014-07-17)
---
- Initial release
