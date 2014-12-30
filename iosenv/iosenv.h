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

static inline BOOL isiOS8OrHigher() {
    return isSystemVersionHigherThanOrEqual(@"8.0");
}

static inline BOOL isJailbroken() {
#if !(TARGET_IPHONE_SIMULATOR)
    if ([[NSFileManager defaultManager] fileExistsAtPath:@"/Applications/Cydia.app"]) {
        return YES;
    }
    else if ([[NSFileManager defaultManager] fileExistsAtPath:@"/Library/MobileSubstrate/MobileSubstrate.dylib"]) {
        return YES;
    }
    else if ([[NSFileManager defaultManager] fileExistsAtPath:@"/bin/bash"]) {
        return YES;
    }
    else if ([[NSFileManager defaultManager] fileExistsAtPath:@"/usr/sbin/sshd"]) {
        return YES;
    }
    else if ([[NSFileManager defaultManager] fileExistsAtPath:@"/etc/apt"]) {
        return YES;
    }
    
    NSError *error;
    NSString *stringToBeWritten = @"This is a test.";
    [stringToBeWritten writeToFile:@"/private/jailbreak.txt" atomically:YES
                          encoding:NSUTF8StringEncoding error:&error];
    if (error==nil){
        return YES;
    } else {
        [[NSFileManager defaultManager] removeItemAtPath:@"/private/jailbreak.txt" error:nil];
    }
    
    if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"cydia://package/com.example.package"]]){
        return YES;
    }
#endif
    
    //All checks have failed. Most probably, the device is not jailbroken
    return NO;
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
    isRetina = [UIScreen.mainScreen respondsToSelector:@selector(scale)] && UIScreen.mainScreen.scale == 2.f;
    return isRetina;
}

static inline BOOL isRetina3xDisplay() {
    BOOL isRetina3x;
    isRetina3x = [UIScreen.mainScreen respondsToSelector:@selector(scale)] && UIScreen.mainScreen.scale == 3.f;
    return isRetina3x;
}

static inline CGFloat mainScreenHeight() {
    //Mainscreen's bounds are orientation-dependent in iOS 8 so using MAX here
    return MAX(CGRectGetHeight(UIScreen.mainScreen.bounds), CGRectGetWidth(UIScreen.mainScreen.bounds));
}

static inline BOOL isiPad() {
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
}


static inline BOOL isiPhone5() {
    return (!isiPad() && mainScreenHeight() == 568.f);
}

static inline BOOL isiPhone6() {
    
    return (!isiPad() && mainScreenHeight() == 667.f && UIScreen.mainScreen.scale == 2.f);
}

static inline BOOL isiPhone6Plus() {
    //scale only == 3.f when running app not in scaled mode
    return (!isiPad() && UIScreen.mainScreen.scale == 3.f);
}

#pragma mark
#pragma mark User agent

static inline NSString *userAgentString() {
    UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectZero];
    NSString *secretAgent = [webView stringByEvaluatingJavaScriptFromString:@"navigator.userAgent"];
    
    return secretAgent;
}

