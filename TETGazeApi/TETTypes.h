/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifndef TETGazeApi_TETTypes_h
#define TETGazeApi_TETTypes_h

/*
 Gaze data
 */
@interface TETEye : NSObject
@property (nonatomic, assign) CGPoint raw; ///< raw gaze coordinates in pixels
@property (nonatomic, assign) CGPoint avg; ///< smoothed coordinates in pix
@property (nonatomic, assign) CGFloat psize;  ///<pupil size
@property (nonatomic, assign) CGPoint pcenter; ///< pupil coordinates normalized
@end

@interface TETGazeData : NSObject

enum
{
    TETGazeDataStateTackingGaze = 1 << 0,
    TETGazeDataStateTrackingEyes = 1 << 1,
    TETGazeDataStateTrackingPresence = 1 << 2,
    TETGazeDataStateTrackingFail = 1 << 3,
    TETGazeDataStateTrackingLost = 1 << 4
};

@property (nonatomic, assign) int time; ///< timestamp
@property (nonatomic, assign) bool fix; ///< is fixated?
@property (nonatomic, assign) int state; ///< 32bit masked state integer
@property (nonatomic, assign) CGPoint raw; ///< raw gaze coordinates in pixels
@property (nonatomic, assign) CGPoint avg; ///< smoothed coordinates in pix
@property (nonatomic, strong) TETEye* lefteye; ///< data for left eye
@property (nonatomic, strong) TETEye* righteye; ///< data for right eye

@end



/*
 Calibration point
 */
typedef struct {
    float ad;
    float adl;
    float adr;
} TETAccuracy;

typedef struct {
    float me;
    float mel;
    float mer;
} TETMeanError;

typedef struct {
    float asd;
    float asdl;
    float asdr;
} TETAvgStdDev;

@interface TETCalibPoint : NSObject
enum {
    TETCalibrationStateNoData,
    TETCalibrationStateResample,
    TETCalibrationStateOk
};
@property (nonatomic, assign) int state; ///< state of calibration point
@property (nonatomic, assign) CGPoint cp; ///< coordinates in pixels
@property (nonatomic, assign) CGPoint mecp; ///< mean estimated coords in pixels
@property (nonatomic, assign) TETAccuracy acd; ///< accuracy in degrees
@property (nonatomic, assign) TETMeanError mepix ; ///< mean error in pixels
@property (nonatomic, assign) TETAvgStdDev asdp; ///< average std deviation in
@end



/*
 Calibration result
 */
@interface TETCalibResult : NSObject
@property (nonatomic, assign) bool result; ///< was the calibration successful?
@property (nonatomic, assign) float deg;  ///< average error in degrees
@property (nonatomic, assign) float degl; ///< average error in degs, left eye
@property (nonatomic, assign) float degr;  ///< average error in degs, right eye
@property (nonatomic, strong) NSMutableArray* calibpoints;
-(void)clear;
@end



/*
 Screen
 */
@interface TETScreen : NSObject
@property (nonatomic, assign) int screenindex;    ///< Screen index
@property (nonatomic, assign) int screenresw;     ///< Screen resolution width in pixels
@property (nonatomic, assign) int screenresh;     ///< Screen resolution height in pixels
@property (nonatomic, assign) float screenpsyw;   ///< Screen physical width in meters
@property (nonatomic, assign) float screenpsyh;   ///< Screen physical height in meters
@end


/*
 Server state
 */
@interface TETServerState : NSObject
enum
{
    TETServerStateTrackerConnected = 0,
    TETServerStateTrackerNotConnected = 1,
    TETServerStateTrackerBadFW = 2,
    TETServerStateTrackerNoUSB3 = 3,
    TETServerStateTrackerNoStream = 4
};

@property (nonatomic, assign) bool push;
@property (nonatomic, assign) int heartbeatinterval;
@property (nonatomic, assign) int version;
@property (nonatomic, assign) int trackerstate;
@property (nonatomic, assign) int framerate;
@property (nonatomic, assign) bool iscalibrated;
@property (nonatomic, assign) bool iscalibrating;
@end

#endif
