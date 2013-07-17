#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma mark
#pragma mark System

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

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

static inline BOOL isIPad () {
    BOOL isIPad;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        // The device is an iPad running iOS 3.2 or later.
        isIpad = YES;
    }
    else {
        // The device is an iPhone or iPod touch.
        isIpad = NO;
    }
    return isIpad;
}

static inline BOOL isIPhone5 () {
    BOOL isIPhone5;
    if (!isIPad() && [[UIScreen mainScreen] bounds].size.height == 568) {
        isIPhone5 = YES;
    }
    else {
        isIPhone5 = NO;
    }
    return isIPhone5;
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

