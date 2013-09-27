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
#pragma mark Interface

static inline UIInterfaceOrientation interfaceOrientation() {
    return UIApplication.sharedApplication.statusBarOrientation;
}

static inline BOOL isPortraitOrientation() {
    return UIInterfaceOrientationIsPortrait(interfaceOrientation());
}

#pragma mark
#pragma mark File system

static inline NSURL *applicationDocumentsDirectoryURL() {
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
}

static inline NSString *applicationDocumentsDirectoryPath() {
    return applicationDocumentsDirectoryURL().path;
}

static inline unsigned long long int folderSize(NSString *folderPath) {
    NSArray *filesArray = [NSFileManager.defaultManager subpathsOfDirectoryAtPath:folderPath error:nil];

    NSString *fileName;
    unsigned long long int fileSize = 0;

    for (fileName in filesArray) {
        NSDictionary *fileDictionary = [NSFileManager.defaultManager attributesOfItemAtPath:[folderPath stringByAppendingPathComponent:fileName] error:nil];
        fileSize += [fileDictionary fileSize];
    }

    return fileSize;
}

#pragma mark
#pragma mark WWW: User agent

static inline NSString *userAgentString() {
    UIWebView* webView = [[UIWebView alloc] initWithFrame:CGRectZero];
    NSString* secretAgent = [webView stringByEvaluatingJavaScriptFromString:@"navigator.userAgent"];

    return secretAgent;
}

#pragma mark
#pragma mark Cleaning

static inline void cleanTemporaryDirectory() {
    NSString *directory = NSTemporaryDirectory();

    NSLog(@"Cleaning temporary directory: %@, %llu", directory, folderSize(directory));

    NSError *error = nil;

    for (NSString *file in [NSFileManager.defaultManager contentsOfDirectoryAtPath:directory error:&error]) {
        NSLog(@"Removing: %@", file);

        [NSFileManager.defaultManager removeItemAtPath:[NSString stringWithFormat:@"%@%@", directory, file] error:&error];

        if (error) {
            NSLog(@"Error deleting file: %@", file);
        }
    }

    NSLog(@"Cleaning completed...");
}

static inline void cleanCookies() {
    NSHTTPCookie *cookie;
    NSHTTPCookieStorage *storage = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for (cookie in [storage cookies])
    {
        [storage deleteCookie:cookie];
    }
}

#pragma mark
#pragma mark Displaying system information

static inline void NSLogCookies() {
    NSHTTPCookie *cookie;
    NSLog(@"==== Cookies ====");
    NSHTTPCookieStorage *storage = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for (cookie in [storage cookies])
    {
        NSLog(@"\tCookie: %@", cookie);
    }
}
static inline void NSLogUserDefaults() {
    NSLog(@"==== NSUserDefaults ====");
    NSLog(@"\t%@", [[NSUserDefaults standardUserDefaults] dictionaryRepresentation]);
}

static inline void NSLogFonts() {
    NSLog(@"==== Available fonts ====");
    NSArray *familyNames = [UIFont familyNames];

    for( NSString *familyName in familyNames ){
        NSLog(@"\tFamily: %s \n", [familyName UTF8String] );

        NSArray *fontNames = [UIFont fontNamesForFamilyName:familyName];
        for( NSString *fontName in fontNames ){
            NSLog(@"\t\tFont: %s\n", [fontName UTF8String] );
        }
    }
}

static inline void NSLogSystemVersion() {
    printf("\n");

    NSLog(@"==== System version ====");
    NSLog(@"%@", UIDevice.currentDevice.systemVersion);

    printf("\n");
}

static inline void NSLogScreenDimensions() {
    printf("\n");
    
    NSLog(@"==== Screen dimensions ====");

    CGRect bounds = UIScreen.mainScreen.bounds;
    NSLog(@"Screen bounds: x:%f, y:%f, width:%f, height:%f", bounds.origin.x, bounds.origin.y, bounds.size.width, bounds.size.height);

    CGRect frame = UIScreen.mainScreen.applicationFrame;
    NSLog(@"Screen application frame: x:%f, y:%f, width:%f, height:%f", frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);

    NSLog(@"Main screen scale: %f", UIScreen.mainScreen.scale);

    NSLog(@"Real screen size: %@", UIScreen.mainScreen.currentMode);

    printf("\n");
}

static inline void NSLogTemporaryDirectoryPath() {
    printf("\n");

    NSLog(@"==== Temporary directory ====");
    NSLog(@"%@", NSTemporaryDirectory());
    
    printf("\n");
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
