#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma mark
#pragma mark System

static inline BOOL isSystemVersionEqualTo(NSString *versionString) {
    return [UIDevice.currentDevice.systemVersion compare:versionString options:NSNumericSearch] == NSOrderedSame;
}

static inline BOOL isSystemVersionHigherThan(NSString *versionString) {
    return [UIDevice.currentDevice.systemVersion compare:versionString options:NSNumericSearch] == NSOrderedDescending;
}

static inline BOOL isSystemVersionHigherThanOrEqual(NSString *versionString) {
    return [UIDevice.currentDevice.systemVersion compare:versionString options:NSNumericSearch] != NSOrderedAscending;
}

static inline BOOL isSystemVersionLessThan(NSString *versionString) {
    return [UIDevice.currentDevice.systemVersion compare:versionString options:NSNumericSearch] == NSOrderedAscending;
}

static inline BOOL isSystemVersionLessThanOrEqual(NSString *versionString) {
    return [UIDevice.currentDevice.systemVersion compare:versionString options:NSNumericSearch] != NSOrderedDescending;
}

static inline BOOL isiOS7OrHigher() {
    return isSystemVersionHigherThanOrEqual(@"7.0");
}

#pragma mark
#pragma mark Project

static inline BOOL isARC() {
#if __has_feature(objc_arc)
    return YES;
#else
    return NO;
#endif
}

#pragma mark
#pragma mark Production or development?

static inline BOOL isSimulator() {
#if TARGET_IPHONE_SIMULATOR
    return YES;
#else
    return NO;
#endif
}

static inline BOOL isProduction() {
#ifdef DEBUG
    return NO;
#else
    return YES;
#endif
}

#pragma mark
#pragma mark Device

static inline BOOL isRetinaDisplay() {
    BOOL isRetina;

    if ([UIScreen.mainScreen respondsToSelector:@selector(scale)] && UIScreen.mainScreen.scale == 2){
        isRetina = YES;
    } else {
        isRetina = NO;
    }

    return isRetina;
}

static inline BOOL isiPad() {
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
}

static inline BOOL isiPhone5() {
    return (isiPad() == NO && CGRectGetHeight(UIScreen.mainScreen.bounds) == 568);
}

#pragma mark
#pragma mark Deprecations

__attribute__((deprecated("Use isSystemVersionEqualTo")))
static inline BOOL SYSTEM_VERSION_EQUAL_TO(NSString *versionString) {
    return isSystemVersionEqualTo(versionString);
}

__attribute__((deprecated("Use isSystemVersionHigherThan")))
static inline BOOL SYSTEM_VERSION_GREATER_THAN(NSString *versionString) {
    return isSystemVersionHigherThan(versionString);
}

__attribute__((deprecated("Use isSystemVersionHigherThanOrEqual")))
static inline BOOL SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(NSString *versionString) {
    return isSystemVersionHigherThanOrEqual(versionString);
}

__attribute__((deprecated("Use isSystemVersionLessThan")))
static inline BOOL SYSTEM_VERSION_LESS_THAN(NSString *versionString) {
    return isSystemVersionLessThan(versionString);
}

__attribute__((deprecated("Use isSystemVersionLessThanOrEqual")))
static inline BOOL SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(NSString *versionString) {
    return isSystemVersionLessThanOrEqual(versionString);
}

__attribute__((deprecated("Naming deprecation: use isiPad() instead")))
static inline BOOL isIPad () {
    return isiPad();
}

__attribute__((deprecated("Naming deprecation: use isiPhone5() instead")))
static inline BOOL isIPhone5() {
    return isiPhone5();
}

__attribute__((deprecated("interfaceOrientation() has been moved into UIKitExtensions project")))
static inline UIInterfaceOrientation interfaceOrientation() {
    return UIApplication.sharedApplication.statusBarOrientation;
}

__attribute__((deprecated("isPortraitOrientation() has been moved into UIKitExtensions project")))
static inline BOOL isPortraitOrientation() {
    return UIInterfaceOrientationIsPortrait(interfaceOrientation());
}
