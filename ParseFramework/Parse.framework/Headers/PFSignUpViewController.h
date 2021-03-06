//
//  PFLogInViewController.h
//  Parse
//
//  Created by Andrew Wang on 3/8/12.
//  Copyright (c) 2012. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Parse/PFSignUpView.h>
#import <Parse/PFUser.h>

@protocol PFSignUpViewControllerDelegate;

/*!
 The class that presents and manages a standard authentication interface for signing up a PFUser.
 */
@interface PFSignUpViewController : UIViewController <UITextFieldDelegate, UIScrollViewDelegate>

/*! @name Configuring Sign Up Elements */

/*!
 A bitmask specifying the sign up elements which are enabled in the view.

     enum {
         PFSignUpFieldsUsernameAndPassword = 0,
         PFSignUpFieldsEmail = 1 << 0,
         PFSignUpFieldsAdditional = 1 << 1, // this field can be used for something else
         PFSignUpFieldsSignUpButton = 1 << 2,
         PFSignUpFieldsDismissButton = 1 << 3,
         PFSignUpFieldsDefault = PFSignUpFieldsUsernameAndPassword | PFSignUpFieldsEmail | PFSignUpFieldsSignUpButton | PFSignUpFieldsDismissButton
     };
 */
@property (nonatomic, assign) PFSignUpFields fields;

/// The sign up view. It contains all the enabled log in elements.
@property (nonatomic, strong, readonly) PFSignUpView *signUpView;

/*! @name Configuring Sign Up Behaviors */

/*!
 The delegate that responds to the control events of PFSignUpViewController.
 */
@property (nonatomic, weak) id<PFSignUpViewControllerDelegate> delegate;

/*!
 Minimum required password length for user signups, defaults to 0.
 */
@property (nonatomic, assign) NSUInteger minPasswordLength;

/*!
 Whether to use the email as username on the attached signUpView.
 If set to YES, we'll hide the email field, prompt for the email in
 the username field, and save the email into both username and email
 fields on the new PFUser object. By default, this is set to NO.
 */
@property (nonatomic, assign) BOOL emailAsUsername;

@end

/*! @name Notifications */

/*!
 The notification is posted immediately after the sign up succeeds.
 */
extern NSString *const PFSignUpSuccessNotification;

/*!
 The notification is posted immediately after the sign up fails.
 If the delegate prevents the sign up to start, the notification is not sent.
 */
extern NSString *const PFSignUpFailureNotification;

/*!
 The notification is posted immediately after the user cancels sign up.
 */
extern NSString *const PFSignUpCancelNotification;

/*!
 The protocol defines methods a delegate of a PFSignUpViewController should implement.
 All methods of the protocol are optional.
 */
@protocol PFSignUpViewControllerDelegate <NSObject>

@optional

/*! @name Customizing Behavior */

/*!
 Sent to the delegate to determine whether the sign up request should be submitted to the server.
 @param signUpController The signup view controller that is requesting the data.
 @param info a dictionary which contains all sign up information that the user entered.
 @result a boolean indicating whether the sign up should proceed.
 */
- (BOOL)signUpViewController:(PFSignUpViewController *)signUpController shouldBeginSignUp:(NSDictionary *)info;

/*!
 Sent to the delegate when a PFUser is signed up.
 @param signUpController The signup view controller where signup finished.
 @param user PFUser object that is a result of the sign up.
 */
- (void)signUpViewController:(PFSignUpViewController *)signUpController didSignUpUser:(PFUser *)user;

/*!
 Sent to the delegate when the sign up attempt fails.
 @param signUpController The signup view controller where signup failed.
 @param error NSError object representing the error that occured.
 */
- (void)signUpViewController:(PFSignUpViewController *)signUpController didFailToSignUpWithError:(NSError *)error;

/*!
 Sent to the delegate when the sign up screen is cancelled.
 @param signUpController The signup view controller where signup was cancelled.
 */
- (void)signUpViewControllerDidCancelSignUp:(PFSignUpViewController *)signUpController;

@end
