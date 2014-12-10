/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#import "TETTypes.h"

#ifndef TETGazeApi_TETGazeListeners_h
#define TETGazeApi_TETGazeListeners_h

/** TETGazeListener
  Callback interface with methods associated to Gaze Tracking.
  This interface should be implemented by classes that are to recieve live GazeData stream.
*/
@protocol TETGazeListener <NSObject>
@required

/** A notification call back indicating that a new GazeData frame is available.
 Implementing classes should update themselves accordingly if needed.
 Register for updates through TETGazeAPI addListener:
 @param gazeData 
        Latest GazeData frame processed by Tracker Server
 */
-(void)onGazeData:(TETGazeData*)gazeData;
@end



/** TETCalibrationResultListener
  Callback interface with methods associated to the changes of calibration result.
  This interface should be implemented by classes that are to recieve only changes in calibration result
  and who are _not_ to perform the calibration process itself.
 */
@protocol TETCalibrationResultListener <NSObject>
@required

/** A notification call back indicating that state of calibration has changed.
 Implementing classes should update themselves accordingly if needed.
 Register for updates through TETGazeAPI addListener:
 
 @param isCalibrated
        is the Tracker Server calibrated?
 @param calibResult
        if calibrated, the currently valid gtl::CalibResult
 */

-(void)onCalibrationChanged:(BOOL)isCalibrated withResult:(TETCalibResult*)calibResult;
@end



/** TETTrackerStateListener
  Callback interface with methods associated to the state of the physical Tracker device.
  This interface should be implemented by classes that are to recieve changes if the state of Tracker
  and handle these accordingly. This could be a class in the 'View' layer telling the user that a
  Tracker has disconnected.
 */
@protocol TETTrackerStateListener <NSObject>
@required

/** A notification call back indicating that state of connected Tracker device has changed.
  Use this to detect if a tracker has been connected or disconnected.
  Implementing classes should update themselves accordingly if needed.
  Register for updates through GazeApi::add_listener(ITrackerStateListener & listener).
 
 @param trackerState 
        the current state of the physical Tracker device
 */
-(void)onTrackerConnectionChanged:(int)trackerState;

/** A notification call back indicating that main screen index has changed.
  This is only relevant for multiscreen setups. Implementing classes should
  update themselves accordingly if needed.
  Register for updates through GazeApi::add_listener(ITrackerStateListener & listener).
 
 @param screen 
        the new screen state
 */
-(void)onScreenStateChanged:(TETScreen*)screen;
@end



/**  TETCalibrationProcessListener
  Callback interface with methods associated to Calibration process.
 */
@protocol TETCalibrationProcessListener <NSObject>
@required

/** Called when a calibration process has been started. */
-(void)onCalibrationStarted;

/** Called every time tracking of a single calibration points has completed.
 @param progress
        'normalized' progress [0..1d]
 */
-(void)onCalibrationProgress:(double)progress;

/** Called when all calibration points have been collected and calibration processing begins. */
-(void)onCalibrationProcessing;

/** Called when processing of calibration points and calibration as a whole has completed.
 
 @param isCalibrated
        is the Tracker Server calibrated?
 @param calibResult
        if calibrated, the currently valid TETCalibResult
 */

-(void)onCalibrationCalibrated:(BOOL)isCalibrated withResult:(TETCalibResult*)calibResult;
@end


/** TETConnectionStateListener
  A notification callback indicating that the connection state has changed.
  Use this to detect if connection the EyeTribe Server has been lost.
  Implementing classes should update themselves accordingly if needed. 
 */
@protocol TETConnectionStateListener <NSObject>
@required

/** Called when tracker received or looses connection  */
-(void)onConnectionStateChanged:(BOOL)isConnected;
@end



#endif
