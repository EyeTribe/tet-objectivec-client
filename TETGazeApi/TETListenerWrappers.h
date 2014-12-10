/*
 * Copyright (c) 2014-present, The Eye Tribe.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in
 * the LICENSE file in the root directory of this source tree.
 *
 */

#ifndef TETGazeApi_TETListenerWrappers_h
#define TETGazeApi_TETListenerWrappers_h

#include "TETHelpers.h"
#include "gazeapi.h"

class TrackerStateListenerWrapper : public gtl::ITrackerStateListener
{
public:
    TrackerStateListenerWrapper(id delegate)
    {
        _delegate = delegate;
    }
    
    virtual void on_tracker_connection_changed(int tracker_state)
    {
        id delegate = _delegate;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onTrackerConnectionChanged:tracker_state];
        });
    }
    
    virtual void on_screen_state_changed(gtl::Screen const & screen)
    {
        id delegate = _delegate;
        gtl::Screen screenData = screen;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onScreenStateChanged:TETScreenFromCppScreen(screenData)];
        });
    }
    
private:
    id _delegate;
};


class GazeListenerWrapper : public gtl::IGazeListener
{
public:
    GazeListenerWrapper(id delegate)
    {
        _delegate = delegate;
    }
    
    virtual void on_gaze_data(gtl::GazeData const & gaze_data)
    {
        id delegate = _delegate;
        gtl::GazeData data = gaze_data;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onGazeData:TETGazeDataFromCppGazeData(data)];
        });
    }
    
private:
    id _delegate;
};


class CalibrationResultListenerWrapper : public gtl::ICalibrationResultListener
{
public:
    CalibrationResultListenerWrapper(id delegate)
    {
        _delegate = delegate;
    }
    
    virtual void on_calibration_changed(bool is_calibrated, gtl::CalibResult const & calib_result)
    {
        id delegate = _delegate;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onCalibrationChanged:is_calibrated withResult:TETCalibResultFromCppCalibResult(calib_result)];
        });
    }
    
    
private:
    id _delegate;
};


class CalibrationProcessHandlerWrapper : public gtl::ICalibrationProcessHandler
{
public:
    CalibrationProcessHandlerWrapper(id delegate)
    {
        _delegate = delegate;
    }
    
    /** Called when a calibration process has been started. */
    virtual void on_calibration_started()
    {
        id delegate = _delegate;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onCalibrationStarted];
        });
    }
    
    /** Called every time tracking of a single calibration points has completed.
     *
     * \param[in] progress'normalized' progress [0..1d]
     */
    virtual void on_calibration_progress(double progress)
    {
        id delegate = _delegate;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onCalibrationProgress:progress];
        });
    }
    
    /** Called when all calibration points have been collected and calibration processing begins. */
    virtual void on_calibration_processing()
    {
        id delegate = _delegate;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onCalibrationProcessing];
        });
    }
    /** Called when processing of calibration points and calibration as a whole has completed.
     *
     * \param[in] is_calibrated is the Tracker Server calibrated?
     * \param[in] calib_result if calibrated, the currently valid gtl::CalibResult
     */
    virtual void on_calibration_result(bool is_calibrated, gtl::CalibResult const & calib_result)
    {
        id delegate = _delegate;
        gtl::CalibResult result = calib_result;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onCalibrationCalibrated:is_calibrated withResult:TETCalibResultFromCppCalibResult(result)];
        });
    }
    
    
private:
    id _delegate;
};


class ConnectionStateChangeListenerWrapper : public gtl::IConnectionStateListener
{
public:
    ConnectionStateChangeListenerWrapper(id delegate)
    {
        _delegate = delegate;
    }
    
    virtual void on_connection_state_changed( bool is_connected )
    {
        id delegate = _delegate;
        dispatch_async(dispatch_get_main_queue(), ^{
            [delegate onConnectionStateChanged:is_connected];
        });
    }
private:
    id _delegate;
};


#endif

