/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#import "TETTypes.h"


/*
 GazeData
 */
@implementation TETEye

@end

@implementation TETGazeData

-(void)dealloc
{
    self.lefteye = nil;
    self.righteye = nil;
}

@end



/*
 Calibration point
 */
@implementation TETCalibPoint

@end



/*
 Calibration result
 */
@implementation TETCalibResult

-(void)clear
{
    self.result = false;
    self.deg = 0.0f;
    self.degl = 0.0f;
    self.degr = 0.0f;
    [self.calibpoints removeAllObjects];
}

-(void)dealloc
{
    self.calibpoints = nil;
}

@end



/*
 Screen
 */
@implementation TETScreen

@end



/*
 Server state
 */
@implementation TETServerState

@end

