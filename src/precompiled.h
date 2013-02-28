#define WINVER 0x0501

#include <node.h>

#include <memory>
#include <iostream>

#include <tuple>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::tr1::shared_ptr;
using std::tr1::static_pointer_cast;
using std::tr1::tuple;
using std::tr1::make_tuple;

#include "ino/platform.h"
#include "ino/macros.h"

#include <CommCtrl.h>
#include <WindowsX.h>

#include "ino/delegates.h"

#include "ino/util.h"
#include "ino/BugCheck.h"
#include "ui/traits.h"
#include "ui/types.h"
