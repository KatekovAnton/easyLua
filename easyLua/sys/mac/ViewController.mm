//
//  ViewController.m
//  easyLuaMac
//
//  Created by Katekov Anton on 8/15/17.
//  Copyright © 2017 katekovanton. All rights reserved.
//

#import "ViewController.h"
#include "UsageSample.hpp"



@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

}

- (void)setRepresentedObject:(id)representedObject
{
    [super setRepresentedObject:representedObject];
}

- (void)viewDidAppear
{
    [super viewDidAppear];
    
    UsageSample sample;
    sample.Test();
}


@end
