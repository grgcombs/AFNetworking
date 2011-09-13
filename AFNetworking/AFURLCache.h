// AFURLCache.h
//
// Copyright (c) 2010-2011 Olivier Poitrey <rs@dailymotion.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished
// to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>

@interface AFURLCache : NSURLCache {
    @private
    dispatch_queue_t _diskCacheQueue;
    dispatch_queue_t _dateFormatterQueue;
    NSString *_diskCachePath;
    NSMutableDictionary *_diskCacheInfo;
    BOOL _diskCacheInfoDirty;
    BOOL _ignoreMemoryOnlyStoragePolicy;
    NSUInteger _diskCacheUsage;
    NSTimeInterval _minCacheInterval;
    NSOperationQueue *_ioQueue;
    NSTimer *_periodicMaintenanceTimer;
    NSOperation *_periodicMaintenanceOperation;
}

/*
 * Defines the minimum number of seconds between now and the expiration time of a cacheable response
 * in order for the response to be cached on disk. This prevent from spending time and storage capacity
 * for an entry which will certainly expire before behing read back from disk cache (memory cache is
 * best suited for short term cache). The default value is set to 5 minutes (300 seconds).
 */
@property (nonatomic, assign) NSTimeInterval minCacheInterval;

/*
 * Allow the responses that have a storage policy of NSURLCacheStorageAllowedInMemoryOnly to be cached
 * on the disk anyway.
 *
 * This is mainly a workaround against cache policies generated by the UIWebViews: starting from iOS 4.2,
 * it always has a cache policy of NSURLCacheStorageAllowedInMemoryOnly.
 * The default value is YES
 */
@property (nonatomic, assign) BOOL ignoreMemoryOnlyStoragePolicy;

/*
 * Returns a default cache director path to be used at cache initialization. The generated path directory
 * will be located in the application's cache directory and thus won't be synced by iTunes.
 */
+ (NSString *)defaultCachePath;

/*
 * Checks if the provided URL exists in cache.
 */
- (BOOL)isCached:(NSURL *)url;

@end
