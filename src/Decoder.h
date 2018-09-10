// Decoder.h

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.

#ifndef APIAI_DECODER_DECODER_H_
#define APIAI_DECODER_DECODER_H_

#include "Request.h"
#include "Response.h"
#include "util/parse-options.h"

#include "base/kaldi-common.h"
#include "util/stl-utils.h"
#include "util/text-utils.h"
#include "util/kaldi-io.h"
#include "fstext/factor.h"
#include "fstext/pre-determinize.h"
#include "fstext/determinize-star.h"

namespace apiai {

/**
 * ASR decoder basic interface
 */
class Decoder {
public:
	virtual ~Decoder() {};

	/** Create decoder clone */
	virtual Decoder *Clone() const = 0;
	/** Register options which can be defined via command line arguments */
	virtual void RegisterOptions(kaldi::OptionsItf &po) = 0;
	/** Initialize decoder */
	virtual bool Initialize(kaldi::OptionsItf &po) = 0;
	/** Perform decoding routine */
	virtual void Decode(Request &request, Response &response) = 0;
};

} /* namespace apiai */

#endif /* APIAI_DECODER_DECODER_H_ */
/*

template<class Arc, class I, class T>
bool GetLinearSymbolSequence(const Fst<Arc> &fst,
                             vector<I> *isymbols_out,
                             vector<I> *osymbols_out,
                             vector<T> *timing_out,
                             typename Arc::Weight *tot_weight_out) {
  typedef typename Arc::StateId StateId;
  typedef typename Arc::Weight Weight;

  Weight tot_weight = Weight::One();
  vector<I> ilabel_seq;
  vector<I> olabel_seq;
  vector<T> timing_seq;

  StateId cur_state = fst.Start();
  if (cur_state == kNoStateId) {  // empty sequence.
    if (isymbols_out != NULL) isymbols_out->clear();
    if (osymbols_out != NULL) osymbols_out->clear();
    if (timing_seq != NULL) timing_seq->clear();
    if (tot_weight_out != NULL) *tot_weight_out = Weight::Zero();
    return true;
  }
  while (1) {
    Weight w = fst.Final(cur_state);
    if (w != Weight::Zero()) {  // is final..
      tot_weight = Times(w, tot_weight);
      if (fst.NumArcs(cur_state) != 0) return false;
      if (isymbols_out != NULL) *isymbols_out = ilabel_seq;
      if (osymbols_out != NULL) *osymbols_out = olabel_seq;
      if (timing_out != NULL) *timing_out = timing_seq;
      if (tot_weight_out != NULL) *tot_weight_out = tot_weight;
      return true;
    } else {
      if (fst.NumArcs(cur_state) != 1) return false;

      ArcIterator<Fst<Arc> > iter(fst, cur_state);  // get the only arc.
      const Arc &arc = iter.Value();
      tot_weight = Times(arc.weight, tot_weight);
      if (arc.ilabel != 0) ilabel_seq.push_back(arc.ilabel);
      if (arc.olabel != 0) olabel_seq.push_back(arc.olabel);
      if (arc.)
      cur_state = arc.nextstate;
    }
  }
}
*/