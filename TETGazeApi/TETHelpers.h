/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifndef TETGazeApi_TETHelpers_h
#define TETGazeApi_TETHelpers_h
#include "gazeapi.h"

/**
 Helpers to convert from cpp structs to objc objects
 */

CGPoint CGPointFromPoint2d(gtl::Point2D const point)
{
    return CGPointMake(point.x, point.y);
}

TETEye* TETEyeFromCppEye(gtl::Eye const& cppEye)
{
    TETEye* eye = [[TETEye alloc] init];
    eye.raw = CGPointFromPoint2d(cppEye.raw);
    eye.avg = CGPointFromPoint2d(cppEye.avg);
    eye.pcenter = CGPointFromPoint2d(cppEye.pcenter);
    eye.psize = cppEye.psize;
    return eye;
}

TETGazeData* TETGazeDataFromCppGazeData(gtl::GazeData const& cppData)
{
    TETGazeData* data = [[TETGazeData alloc] init];
    data.time = cppData.time;
    data.fix = cppData.fix;
    data.state = cppData.state;
    data.raw = CGPointFromPoint2d(cppData.raw);
    data.avg = CGPointFromPoint2d(cppData.avg);
    data.lefteye = TETEyeFromCppEye(cppData.lefteye);
    data.righteye = TETEyeFromCppEye(cppData.righteye);
    return data;
}

TETCalibPoint* TETCalibPointFromCppCalibPoint(gtl::CalibPoint const& cppCalibPoint)
{
    TETCalibPoint* calibPoint = [[TETCalibPoint alloc] init];
    calibPoint.state = cppCalibPoint.state;
    calibPoint.cp = CGPointFromPoint2d(cppCalibPoint.cp);
    calibPoint.mecp = CGPointFromPoint2d(cppCalibPoint.mecp);
    TETAccuracy acd = {cppCalibPoint.acd.ad,cppCalibPoint.acd.adl,cppCalibPoint.acd.adr};
    calibPoint.acd = acd;
    TETMeanError mepix = {cppCalibPoint.mepix.mep, cppCalibPoint.mepix.mepl, cppCalibPoint.mepix.mepr};
    calibPoint.mepix = mepix;
    TETAvgStdDev asdp = {cppCalibPoint.acd.ad, cppCalibPoint.acd.adl, cppCalibPoint.acd.adr};
    calibPoint.asdp = asdp;
    return calibPoint;
}

TETCalibResult* TETCalibResultFromCppCalibResult(gtl::CalibResult const& cppResult)
{
    TETCalibResult* result = [[TETCalibResult alloc] init];
    result.result = cppResult.result;
    result.deg = cppResult.deg;
    result.degl = cppResult.degl;
    result.degr = cppResult.degr;
    result.calibpoints = [[NSMutableArray alloc] initWithCapacity:cppResult.calibpoints.size()];
    for(int i = 0; i < cppResult.calibpoints.size(); i++) {
        [result.calibpoints addObject:TETCalibPointFromCppCalibPoint(cppResult.calibpoints[i])];
    }
    
    return result;
}

TETServerState* TETServerStateFromCppServerState(gtl::ServerState const & cppServerState)
{
    TETServerState* serverState = [[TETServerState alloc] init];
    serverState.push = cppServerState.push;
    serverState.heartbeatinterval = cppServerState.heartbeatinterval;
    serverState.version = cppServerState.version;
    serverState.trackerstate = cppServerState.trackerstate;
    serverState.framerate = cppServerState.framerate;
    serverState.iscalibrated = cppServerState.iscalibrated;
    serverState.iscalibrating = cppServerState.iscalibrating;
    return serverState;
}

TETScreen* TETScreenFromCppScreen(gtl::Screen const& cppScreen)
{
    TETScreen* screen = [[TETScreen alloc] init];
    screen.screenindex = cppScreen.screenindex;
    screen.screenresw = cppScreen.screenresw;
    screen.screenresh = cppScreen.screenresh;
    screen.screenpsyw = cppScreen.screenpsyw;
    screen.screenresh = cppScreen.screenpsyh;
    return screen;
}


#endif
