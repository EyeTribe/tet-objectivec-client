/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#include <stdio.h>
#import "TETGazeApi.h"
#import "TETListeners.h"
#import "TETListenerWrappers.h"
#import "TETHelpers.h"
#include "gazeapi.h"


@interface TETListener : NSObject
@property (nonatomic) CalibrationResultListenerWrapper* calibrationResultListenerWrapper;
@property (nonatomic) CalibrationProcessHandlerWrapper* calibrationProcessHandler;
@property (nonatomic) TrackerStateListenerWrapper* trackerStateListener;
@property (nonatomic) GazeListenerWrapper* gazeListenerWrapper;
-(void)setObject:(id)object;
-(id)object;
@end

@implementation TETListener
{
    __unsafe_unretained id _object; // unsafe unretained due to osx 10.7
}

-(void)setObject:(id)object
{
    _object = object;
}

-(id)object
{
    return _object;
}

-(void)dealloc
{
    if(self.calibrationResultListenerWrapper) delete self.calibrationResultListenerWrapper;
    if(self.calibrationProcessHandler) delete self.calibrationProcessHandler;
    if(self.trackerStateListener) delete self.trackerStateListener;
    if(self.gazeListenerWrapper) delete self.gazeListenerWrapper;
}

@end


@implementation TETGazeAPI
{
    gtl::GazeApi* api;
    NSMutableArray* listeners;
}

-(id)init
{
    self = [super init];
    if(self != nil) {
        api = new gtl::GazeApi(false);
        listeners = [[NSMutableArray alloc] init];
    }
    return self;
}

-(void)dealloc
{
    if(api) delete api;
}

-(void)addListener:(id)listener
{
    // remove old listeners
    [self removeListener:listener];
    
    // add new listener
    TETListener* tetlistener = [[TETListener alloc] init];
    tetlistener.object = listener;
    [listeners addObject:tetlistener];
    
    
    // add calibration result listener
    if([listener conformsToProtocol:@protocol(TETCalibrationResultListener)]) {
        tetlistener.calibrationResultListenerWrapper = new CalibrationResultListenerWrapper(listener);
        api->add_listener(*tetlistener.calibrationResultListenerWrapper);
    }
    
    // add calibration process listener
    if([listener conformsToProtocol:@protocol(TETCalibrationProcessListener)]) {
        tetlistener.calibrationProcessHandler = new CalibrationProcessHandlerWrapper(listener);
        api->add_listener(*tetlistener.calibrationProcessHandler);
    }
    
    // add tracker state listener
    if([listener conformsToProtocol:@protocol(TETTrackerStateListener)]) {
        tetlistener.trackerStateListener = new TrackerStateListenerWrapper(listener);
        api->add_listener(*tetlistener.trackerStateListener);
    }
    
    
    // add gaze listener
    if([listener conformsToProtocol:@protocol(TETGazeListener)]) {
        tetlistener.gazeListenerWrapper = new GazeListenerWrapper(listener);
        api->add_listener(*tetlistener.gazeListenerWrapper);
    }
    
}

-(void)removeListener:(id)listener
{
    for(TETListener* tetlistener in listeners) {
        if(tetlistener.object == listener) {
            [self removeTETListener:tetlistener];
            return;
        }
    }
}

-(void)removeTETListener:(TETListener*)tetlistener
{
    if(tetlistener.calibrationResultListenerWrapper) api->remove_listener(*tetlistener.calibrationResultListenerWrapper);
    if(tetlistener.calibrationProcessHandler) api->remove_listener(*tetlistener.calibrationProcessHandler);
    if(tetlistener.trackerStateListener) api->remove_listener(*tetlistener.trackerStateListener);
    if(tetlistener.gazeListenerWrapper) api->remove_listener(*tetlistener.gazeListenerWrapper);
    [listeners removeObject:tetlistener];
}

-(BOOL)isConnected
{
    return api->is_connected();
}

-(BOOL)connectWithPushMode:(BOOL)pushMode
{
    return api->connect(pushMode);
}

-(BOOL)connectWithPushMode:(BOOL)pushMode hostname:(NSString*)hostname andPort:(int)port
{
    return api->connect(pushMode, [hostname UTF8String], port);
}


-(void)disconnect
{
    api->disconnect();
}

-(void)setPush:(BOOL)enable
{
    api->set_push(enable);
}

-(void)setScreen:(TETScreen*)screen
{
    gtl::Screen cppScreen;
    cppScreen.screenindex = screen.screenindex;
    cppScreen.screenresw = screen.screenresw;
    cppScreen.screenresh = screen.screenresh;
    cppScreen.screenpsyw = screen.screenpsyw;
    cppScreen.screenpsyh = screen.screenpsyh;
    api->set_screen(cppScreen);
}

-(TETScreen*)screen
{
    gtl::Screen cppScreen;
    api->get_screen(cppScreen);
    TETScreen* screen = [[TETScreen alloc] init];
    screen.screenindex = cppScreen.screenindex;
    screen.screenresw = cppScreen.screenresw;
    screen.screenresh = cppScreen.screenresh;
    screen.screenpsyw = cppScreen.screenpsyw;
    screen.screenpsyh = cppScreen.screenpsyh;
    return screen;
}

-(TETGazeData*)frameData
{
    gtl::GazeData cppData;
    api->get_frame(cppData);
    return TETGazeDataFromCppGazeData(cppData);
}

-(TETCalibResult*)calibResult
{
    gtl::CalibResult calibResult;
    api->get_calib_result(calibResult);
    return TETCalibResultFromCppCalibResult(calibResult);
}
-(TETServerState*)serverState
{
    return TETServerStateFromCppServerState(api->get_server_state());
}

-(BOOL)calibrationStart:(int)pointCount
{
    return api->calibration_start(pointCount);
}

-(void)calibrationClear
{
    api->calibration_clear();
}
-(void)calibrationAbort
{
    api->calibration_abort();
}
-(void)calibrationPointStart:(CGPoint)point
{
    api->calibration_point_start(point.x, point.y);
}
-(void)calibrationPointEnd
{
    api->calibration_point_end();
}


@end