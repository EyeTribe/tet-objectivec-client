/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifndef TheEyeTribeUI_GazeAPI_h
#define TheEyeTribeUI_GazeAPI_h

#import "TETListeners.h"

/*
 * This is the main interface point into the GaziApi library for communicating and controlling The Eyetribe Tracker server
 */
@interface TETGazeAPI : NSObject

/** Add an listener to the GazeApi.
 @param listener
        Object to receive callbacks, should conform to one of the protocols found in TETListeners.h
  */
-(void)addListener:(id)listener;

/** Remove an IGazeListener from the GazeApi.
 */
-(void)removeListener:(id)listener;

/** Has a connection to the server been established?
 @return True if connected, false if not.
 */
-(BOOL)isConnected;

/** Connect to the server via default port.
 @return True if connected, false if connection failed.
 */
-(BOOL)connect;

/** Connect to the server via specified port.
 @param hostname
        Default host is localhost'.
 @param port 
        Number to connect to server on.
 @return True if connected, false if connection failed.
 */
-(BOOL)connectWithPort:(int)port;

/** Disconnect from server. */
-(void)disconnect;

/** Set screen parameters.
 @param screen
        the Screen parameters to be set.
 @return True if successful and the screen parameters are valid, false if not.
 */
-(BOOL)setScreen:(TETScreen*)screen;

/** Get current used screen parameters.
 @param screen
        The Screen parameters to be retrieved.
 */
-(TETScreen*)screen;

/** Get current GazeData
  Attempts to retrieve the current valid GazeData. If push-mode is enabled gaze_data is filled with the latest valid GazeData.
  If push-mode is disabled the method requests the latest GazeData from the server and fills out gaze_data when it is available.
 
  In pull-mode this is a blocking call. The method does not terminate before a new GazeData has been delivered.
  In push-mode the GazeApi will fire an IGazeListener::on_gaze_data(gtl::GazeData const & gaze_data) containing the latest GazeData.
 
 @return Valid GazeData if push-mode enabled, invalid otherwise.
 */
-(TETGazeData*)frameData;

/** Get current valid calibration
 @param calib_result 
        latest valid calibration result.
 */
-(TETCalibResult*)calibResult;

/** Read the current server state.
 @return ServerState the current server state.
 */
-(TETServerState*)serverState;

/** Begin new calibration sesssion.
 @param pointCount
        The number of points to use for calibration.
 @return indication of the request processed okay.
 */
-(BOOL)calibrationStart:(int)pointCount;

/** Clears the current server calibration but does not affect an ongoing calibration session.
 */
-(void)calibrationClear;

/** Aborts the current calibration session, but does not clear any valid calibration in the server
 */
-(void)calibrationAbort;

/** Begin calibration a new calibration point.
 @param point
        Calibration point
 */
-(void)calibrationPointStart:(CGPoint)point;

/** End current calibration point.
 */
-(void)calibrationPointEnd;

@end

#endif ///_THEEYETRIBE_GAZEAPI_H_
