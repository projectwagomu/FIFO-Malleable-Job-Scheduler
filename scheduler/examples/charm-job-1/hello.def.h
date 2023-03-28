

/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_Main::initDone_2_closure : public SDAG::Closure {
      

      initDone_2_closure() {
        init();
      }
      initDone_2_closure(CkMigrateMessage*) {
        init();
      }
            void pup(PUP::er& __p) {
        packClosure(__p);
      }
      virtual ~initDone_2_closure() {
      }
      PUPable_decl(SINGLE_ARG(initDone_2_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_Main::done_3_closure : public SDAG::Closure {
      

      done_3_closure() {
        init();
      }
      done_3_closure(CkMigrateMessage*) {
        init();
      }
            void pup(PUP::er& __p) {
        packClosure(__p);
      }
      virtual ~done_3_closure() {
      }
      PUPable_decl(SINGLE_ARG(done_3_closure));
    };
#endif /* CK_TEMPLATES_ONLY */


/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_Hello::SayHi_2_closure : public SDAG::Closure {
            int hiNo;


      SayHi_2_closure() {
        init();
      }
      SayHi_2_closure(CkMigrateMessage*) {
        init();
      }
            int & getP0() { return hiNo;}
      void pup(PUP::er& __p) {
        __p | hiNo;
        packClosure(__p);
      }
      virtual ~SayHi_2_closure() {
      }
      PUPable_decl(SINGLE_ARG(SayHi_2_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */


/* DEFS: readonly CProxy_Main mainProxy;
 */
extern CProxy_Main mainProxy;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_mainProxy(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|mainProxy;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly int nElements;
 */
extern int nElements;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_nElements(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|nElements;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
void initDone();
void done();
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_Main::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: Main(CkArgMsg* impl_msg);
 */

CkChareID CProxy_Main::ckNew(CkArgMsg* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, &impl_ret, impl_onPE);
  return impl_ret;
}

void CProxy_Main::ckNew(CkArgMsg* impl_msg, CkChareID* pcid, int impl_onPE)
{
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, pcid, impl_onPE);
}

  CProxy_Main::CProxy_Main(CkArgMsg* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, &impl_ret, impl_onPE);
  ckSetChareID(impl_ret);
}

// Entry point registration function

int CkIndex_Main::reg_Main_CkArgMsg() {
  int epidx = CkRegisterEp("Main(CkArgMsg* impl_msg)",
      _call_Main_CkArgMsg, CMessage_CkArgMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)CkArgMsg::ckDebugPup);
  return epidx;
}


void CkIndex_Main::_call_Main_CkArgMsg(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  new (impl_obj_void) Main((CkArgMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initDone();
 */

void CProxy_Main::initDone(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
  if (ckIsDelegated()) {
    int destPE=CkChareMsgPrep(CkIndex_Main::idx_initDone_void(), impl_msg, &ckGetChareID());
    if (destPE!=-1) ckDelegatedTo()->ChareSend(ckDelegatedPtr(),CkIndex_Main::idx_initDone_void(), impl_msg, &ckGetChareID(),destPE);
  } else {
    CkSendMsg(CkIndex_Main::idx_initDone_void(), impl_msg, &ckGetChareID(),0);
  }
}

// Entry point registration function

int CkIndex_Main::reg_initDone_void() {
  int epidx = CkRegisterEp("initDone()",
      _call_initDone_void, 0, __idx, 0);
  return epidx;
}


void CkIndex_Main::_call_initDone_void(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  CkFreeSysMsg(impl_msg);
  impl_obj->initDone();
}
PUPable_def(SINGLE_ARG(Closure_Main::initDone_2_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void done();
 */

void CProxy_Main::done(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
  if (ckIsDelegated()) {
    int destPE=CkChareMsgPrep(CkIndex_Main::idx_done_void(), impl_msg, &ckGetChareID());
    if (destPE!=-1) ckDelegatedTo()->ChareSend(ckDelegatedPtr(),CkIndex_Main::idx_done_void(), impl_msg, &ckGetChareID(),destPE);
  } else {
    CkSendMsg(CkIndex_Main::idx_done_void(), impl_msg, &ckGetChareID(),0);
  }
}

// Entry point registration function

int CkIndex_Main::reg_done_void() {
  int epidx = CkRegisterEp("done()",
      _call_done_void, 0, __idx, 0);
  return epidx;
}


void CkIndex_Main::_call_done_void(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  CkFreeSysMsg(impl_msg);
  impl_obj->done();
}
PUPable_def(SINGLE_ARG(Closure_Main::done_3_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_Main::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeMainChare);
  CkRegisterBase(__idx, CkIndex_Chare::__idx);
  // REG: Main(CkArgMsg* impl_msg);
  idx_Main_CkArgMsg();
  CkRegisterMainChare(__idx, idx_Main_CkArgMsg());

  // REG: void initDone();
  idx_initDone_void();

  // REG: void done();
  idx_done_void();

}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: array Hello: ArrayElement{
Hello();
void SayHi(int hiNo);
Hello(CkMigrateMessage* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_Hello::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CProxySection_Hello::contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData, int fragSize)
{
   CkArray *ckarr = CProxy_CkArray(sid.get_aid()).ckLocalBranch();
   CkMulticastMgr *mCastGrp = CProxy_CkMulticastMgr(ckarr->getmCastMgr()).ckLocalBranch();
   mCastGrp->contribute(dataSize, data, type, sid, userData, fragSize);
}

void CProxySection_Hello::contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, CkCallback &cb, int userData, int fragSize)
{
   CkArray *ckarr = CProxy_CkArray(sid.get_aid()).ckLocalBranch();
   CkMulticastMgr *mCastGrp = CProxy_CkMulticastMgr(ckarr->getmCastMgr()).ckLocalBranch();
   mCastGrp->contribute(dataSize, data, type, sid, cb, userData, fragSize);
}

#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: Hello();
 */

void CProxyElement_Hello::insert(int onPE, const CkEntryOptions *impl_e_opts)
{ 
   static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
   UsrToEnv(impl_msg)->setMsgtype(ArrayEltInitMsg);
   ckInsert((CkArrayMessage *)impl_msg,CkIndex_Hello::idx_Hello_void(),onPE);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void SayHi(int hiNo);
 */

void CProxyElement_Hello::SayHi(int hiNo, const CkEntryOptions *impl_e_opts) 
{
  ckCheck();
  //Marshall: int hiNo
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|hiNo;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|hiNo;
  }
  UsrToEnv(impl_msg)->setMsgtype(ForArrayEltMsg);
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_Hello::idx_SayHi_marshall2(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: Hello(CkMigrateMessage* impl_msg);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: Hello();
 */

CkArrayID CProxy_Hello::ckNew(const CkArrayOptions &opts, const CkEntryOptions *impl_e_opts)
{
  static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
  UsrToEnv(impl_msg)->setMsgtype(ArrayEltInitMsg);
  CkArrayID gId = ckCreateArray((CkArrayMessage *)impl_msg, CkIndex_Hello::idx_Hello_void(), opts);
  return gId;
}

void CProxy_Hello::ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts)
{
  static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
  UsrToEnv(impl_msg)->setMsgtype(ArrayEltInitMsg);
  CkSendAsyncCreateArray(CkIndex_Hello::idx_Hello_void(), _ck_array_creation_cb, opts, impl_msg);
}

CkArrayID CProxy_Hello::ckNew(const int s1, const CkEntryOptions *impl_e_opts)
{
  static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
  CkArrayOptions opts(s1);
  UsrToEnv(impl_msg)->setMsgtype(ArrayEltInitMsg);
  CkArrayID gId = ckCreateArray((CkArrayMessage *)impl_msg, CkIndex_Hello::idx_Hello_void(), opts);
  return gId;
}

void CProxy_Hello::ckNew(const int s1, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts)
{
  static_cast<void>(impl_e_opts);
  void *impl_msg = CkAllocSysMsg();
  CkArrayOptions opts(s1);
  UsrToEnv(impl_msg)->setMsgtype(ArrayEltInitMsg);
  CkSendAsyncCreateArray(CkIndex_Hello::idx_Hello_void(), _ck_array_creation_cb, opts, impl_msg);
}

// Entry point registration function

int CkIndex_Hello::reg_Hello_void() {
  int epidx = CkRegisterEp("Hello()",
      _call_Hello_void, 0, __idx, 0);
  return epidx;
}


void CkIndex_Hello::_call_Hello_void(void* impl_msg, void* impl_obj_void)
{
  Hello* impl_obj = static_cast<Hello *>(impl_obj_void);
  CkFreeSysMsg(impl_msg);
  new (impl_obj_void) Hello();
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void SayHi(int hiNo);
 */

void CProxy_Hello::SayHi(int hiNo, const CkEntryOptions *impl_e_opts) 
{
  ckCheck();
  //Marshall: int hiNo
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|hiNo;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|hiNo;
  }
  UsrToEnv(impl_msg)->setMsgtype(ForArrayEltMsg);
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckBroadcast(impl_amsg, CkIndex_Hello::idx_SayHi_marshall2(),0);
}

// Entry point registration function

int CkIndex_Hello::reg_SayHi_marshall2() {
  int epidx = CkRegisterEp("SayHi(int hiNo)",
      _call_SayHi_marshall2, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_SayHi_marshall2);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_SayHi_marshall2);

  return epidx;
}


void CkIndex_Hello::_call_SayHi_marshall2(void* impl_msg, void* impl_obj_void)
{
  Hello* impl_obj = static_cast<Hello *>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  /*Unmarshall pup'd fields: int hiNo*/
  PUP::fromMem implP(impl_buf);
  int hiNo; implP|hiNo;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->SayHi(hiNo);
}

int CkIndex_Hello::_callmarshall_SayHi_marshall2(char* impl_buf, void* impl_obj_void) {
  Hello* impl_obj = static_cast< Hello *>(impl_obj_void);
  /*Unmarshall pup'd fields: int hiNo*/
  PUP::fromMem implP(impl_buf);
  int hiNo; implP|hiNo;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->SayHi(hiNo);
  return implP.size();
}

void CkIndex_Hello::_marshallmessagepup_SayHi_marshall2(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  /*Unmarshall pup'd fields: int hiNo*/
  PUP::fromMem implP(impl_buf);
  int hiNo; implP|hiNo;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("hiNo");
  implDestP|hiNo;
}
PUPable_def(SINGLE_ARG(Closure_Hello::SayHi_2_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: Hello(CkMigrateMessage* impl_msg);
 */

// Entry point registration function

int CkIndex_Hello::reg_Hello_CkMigrateMessage() {
  int epidx = CkRegisterEp("Hello(CkMigrateMessage* impl_msg)",
      _call_Hello_CkMigrateMessage, 0, __idx, 0);
  return epidx;
}


void CkIndex_Hello::_call_Hello_CkMigrateMessage(void* impl_msg, void* impl_obj_void)
{
  call_migration_constructor<Hello> c = impl_obj_void;
  c((CkMigrateMessage*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: Hello();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void SayHi(int hiNo);
 */

void CProxySection_Hello::SayHi(int hiNo, const CkEntryOptions *impl_e_opts) 
{
  ckCheck();
  //Marshall: int hiNo
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|hiNo;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|hiNo;
  }
  UsrToEnv(impl_msg)->setMsgtype(ForArrayEltMsg);
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_Hello::idx_SayHi_marshall2(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: Hello(CkMigrateMessage* impl_msg);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_Hello::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeArray);
  CkRegisterBase(__idx, CkIndex_ArrayElement::__idx);
  // REG: Hello();
  idx_Hello_void();
  CkRegisterDefaultCtor(__idx, idx_Hello_void());

  // REG: void SayHi(int hiNo);
  idx_SayHi_marshall2();

  // REG: Hello(CkMigrateMessage* impl_msg);
  idx_Hello_CkMigrateMessage();
  CkRegisterMigCtor(__idx, idx_Hello_CkMigrateMessage());

}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void _registerhello(void)
{
  static int _done = 0; if(_done) return; _done = 1;
  CkRegisterReadonly("mainProxy","CProxy_Main",sizeof(mainProxy),(void *) &mainProxy,__xlater_roPup_mainProxy);

  CkRegisterReadonly("nElements","int",sizeof(nElements),(void *) &nElements,__xlater_roPup_nElements);

/* REG: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
void initDone();
void done();
};
*/
  CkIndex_Main::__register("Main", sizeof(Main));

/* REG: array Hello: ArrayElement{
Hello();
void SayHi(int hiNo);
Hello(CkMigrateMessage* impl_msg);
};
*/
  CkIndex_Hello::__register("Hello", sizeof(Hello));

}
extern "C" void CkRegisterMainModule(void) {
  _registerhello();
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_Main::virtual_pup(PUP::er &p) {
    recursive_pup<Main >(dynamic_cast<Main* >(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_Hello::virtual_pup(PUP::er &p) {
    recursive_pup<Hello >(dynamic_cast<Hello* >(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
