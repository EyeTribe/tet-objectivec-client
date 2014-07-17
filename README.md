Objective-C SDK for The Eye Tribe Tracker
====

Introduction
----

This is the Objective-C reference implementation for The Eye Tribe Tracker and provides a simple Objective-C interface for communicating with the server through the open [TET API](http://dev.theeyetribe.com/api/). This allows developers to easily get started and focus their energy on creating innovative and immersive apps using our eye tracking technology. 

This implementation is simple of nature and wraps the [C++ SDK](https://github.com/EyeTribe/tet-cpp-client)

This version is to be considered _alpha_. Feedback and bug fix submissions are welcome.

Please visit http://dev.theeyetribe.com for more information.


Compilation
----

To compile this project, you need Xcode 5 or higher as well as Xcode command line tools. Both can be downloaded from the [Apple Mac Devcenter](https://developer.apple.com/devcenter/mac).


Dependencies
----

The dependencies of the [C++ SDK](https://github.com/EyeTribe/tet-cpp-client) also applies to this Objective-C wrapper.


Build
----

First, install Boost as explained in the [C++ SDK](https://github.com/EyeTribe/tet-cpp-client) build section.

Next, simply open the workspace file in Xcode and build the TETGazeApi scheme.


Samples
----

There are currently no samples available for the Objective-C SDK, but they will be added as they become available.


API Reference
----

The complete API specification used by the Objective-C SDK to communicate with the server is available on our [developer website](http://dev.theeyetribe.com/api/).


Changelog
----
0.9.36 (2014-07-17)
- Initial release
