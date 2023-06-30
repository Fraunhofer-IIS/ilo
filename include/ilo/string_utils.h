/*-----------------------------------------------------------------------------
Software License for The Fraunhofer FDK MPEG-H Software

Copyright (c) 2016 - 2023 Fraunhofer-Gesellschaft zur Förderung der angewandten
Forschung e.V. and Contributors
All rights reserved.

1. INTRODUCTION

The "Fraunhofer FDK MPEG-H Software" is software that implements the ISO/MPEG
MPEG-H 3D Audio standard for digital audio or related system features. Patent
licenses for necessary patent claims for the Fraunhofer FDK MPEG-H Software
(including those of Fraunhofer), for the use in commercial products and
services, may be obtained from the respective patent owners individually and/or
from Via LA (www.via-la.com).

Fraunhofer supports the development of MPEG-H products and services by offering
additional software, documentation, and technical advice. In addition, it
operates the MPEG-H Trademark Program to ease interoperability testing of end-
products. Please visit www.mpegh.com for more information.

2. COPYRIGHT LICENSE

Redistribution and use in source and binary forms, with or without modification,
are permitted without payment of copyright license fees provided that you
satisfy the following conditions:

* You must retain the complete text of this software license in redistributions
of the Fraunhofer FDK MPEG-H Software or your modifications thereto in source
code form.

* You must retain the complete text of this software license in the
documentation and/or other materials provided with redistributions of
the Fraunhofer FDK MPEG-H Software or your modifications thereto in binary form.
You must make available free of charge copies of the complete source code of
the Fraunhofer FDK MPEG-H Software and your modifications thereto to recipients
of copies in binary form.

* The name of Fraunhofer may not be used to endorse or promote products derived
from the Fraunhofer FDK MPEG-H Software without prior written permission.

* You may not charge copyright license fees for anyone to use, copy or
distribute the Fraunhofer FDK MPEG-H Software or your modifications thereto.

* Your modified versions of the Fraunhofer FDK MPEG-H Software must carry
prominent notices stating that you changed the software and the date of any
change. For modified versions of the Fraunhofer FDK MPEG-H Software, the term
"Fraunhofer FDK MPEG-H Software" must be replaced by the term "Third-Party
Modified Version of the Fraunhofer FDK MPEG-H Software".

3. No PATENT LICENSE

NO EXPRESS OR IMPLIED LICENSES TO ANY PATENT CLAIMS, including without
limitation the patents of Fraunhofer, ARE GRANTED BY THIS SOFTWARE LICENSE.
Fraunhofer provides no warranty of patent non-infringement with respect to this
software. You may use this Fraunhofer FDK MPEG-H Software or modifications
thereto only for purposes that are authorized by appropriate patent licenses.

4. DISCLAIMER

This Fraunhofer FDK MPEG-H Software is provided by Fraunhofer on behalf of the
copyright holders and contributors "AS IS" and WITHOUT ANY EXPRESS OR IMPLIED
WARRANTIES, including but not limited to the implied warranties of
merchantability and fitness for a particular purpose. IN NO EVENT SHALL THE
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE for any direct, indirect,
incidental, special, exemplary, or consequential damages, including but not
limited to procurement of substitute goods or services; loss of use, data, or
profits, or business interruption, however caused and on any theory of
liability, whether in contract, strict liability, or tort (including
negligence), arising in any way out of the use of this software, even if
advised of the possibility of such damage.

5. CONTACT INFORMATION

Fraunhofer Institute for Integrated Circuits IIS
Attention: Division Audio and Media Technologies - MPEG-H FDK
Am Wolfsmantel 33
91058 Erlangen, Germany
www.iis.fraunhofer.de/amm
amm-info@iis.fraunhofer.de
-----------------------------------------------------------------------------*/

/*!
 * @file string_utils.h
 * @brief String utilities
 */

#pragma once

// System includes
#include <string>
#include <deque>
#include <algorithm>
#include <sstream>
#include <stdexcept>

// Internal includes
#include "ilo/version.h"
#include "ilo/common_types.h"

namespace ilo {
/*! \defgroup StringUtils String utilities
 *  @{
 *  Collection of helpers related to string processing and conversion.
 */

/** @name FourCC helper tools */
/**@{*/

//! Convert a FourCC type to a string
std::string toString(const Fourcc& fcc);
/*! Convert a string to an Fourcc type */
Fourcc toFcc(const std::string str);

/**@}*/

/** @name IsoLang helper tools */
/**@{*/

//! Convert an IsoLang type to a string
std::string toString(const IsoLang& isoLang);
//! Convert a string to an IsoLang type
IsoLang toIsoLang(const std::string str);

/**@}*/

//! Tokenizer separating a string at user defined separators
template <class string_type, class char_type>
std::deque<std::string> tokenize(const string_type& source, const char_type sep) {
  std::deque<std::string> result;
  auto begin = source.begin();
  typename string_type::const_iterator next;
  while ((next = std::find(begin, source.end(), sep)) != source.end()) {
    result.push_back(string_type(begin, next));
    begin = next + 1;
  }
  result.push_back(string_type(begin, next));

  return result;
}

/*!
 * @brief Function to convert a string into int/uint values
 *
 * @note int8_t and uint8_t are not supported!\n
 * If the type is not compatible it will throw a runtime_error exception.\n
 * Please note that when converting negative values the target type must be an integer type.
 * Otherwise the value might implicitly be interpreted in a wrong way.\n
 */
template <typename T>
T convertString(const std::string& valueString) {
  std::istringstream ss(valueString);
  T value = 0;
  if (!(ss >> value) || ss.fail()) {
    throw std::runtime_error("String conversion of " + valueString + " failed");
  }

  if (!ss.peek() || !ss.eof()) {
    throw std::runtime_error("String conversion of " + valueString + " failed");
  }
  return value;
}
/**@}*/
}  // namespace ilo
