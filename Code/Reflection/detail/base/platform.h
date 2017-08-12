//
//  Header.h
//  RefLib
//
//  Created by sunnior on 8/12/17.
//  Copyright (c) 2017 sunnior. All rights reserved.
//

#ifndef __REFL_PLATFORM_H__
#define __REFL_PLATFORM_H__

#if defined(__clang__)
#define REFL_COMPILER_CLANG
#elif defined(_MSC_VER)
#define REFL_COMPILER_MSVC
#endif

#endif
