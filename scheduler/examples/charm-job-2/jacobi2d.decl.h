#ifndef _DECL_jacobi2d_H_
#define _DECL_jacobi2d_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
/* DECLS: readonly CProxy_Main mainProxy;
 */

/* DECLS: readonly int array_height;
 */

/* DECLS: readonly int array_width;
 */

/* DECLS: readonly int block_height;
 */

/* DECLS: readonly int block_width;
 */

/* DECLS: readonly int num_chare_rows;
 */

/* DECLS: readonly int num_chare_cols;
 */

/* DECLS: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
void report(int completed_iteration);
Main(CkMigrateMessage* impl_msg);
};
 */
 class Main;
 class CkIndex_Main;
 class CProxy_Main;
/* --------------- index object ------------------ */
class CkIndex_Main:public CkIndex_Chare{
  public:
    typedef Main local_t;
    typedef CkIndex_Main index_t;
    typedef CProxy_Main proxy_t;
    typedef CProxy_Main element_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: Main(CkArgMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Main_CkArgMsg();
    // Entry point index lookup
    
    inline static int idx_Main_CkArgMsg() {
      static int epidx = reg_Main_CkArgMsg();
      return epidx;
    }

    
    static int ckNew(CkArgMsg* impl_msg) { return idx_Main_CkArgMsg(); }
    
    static void _call_Main_CkArgMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Main_CkArgMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void report(int completed_iteration);
     */
    // Entry point registration at startup
    
    static int reg_report_marshall2();
    // Entry point index lookup
    
    inline static int idx_report_marshall2() {
      static int epidx = reg_report_marshall2();
      return epidx;
    }

    
    inline static int idx_report(void (Main::*)(int completed_iteration) ) {
      return idx_report_marshall2();
    }


    
    static int report(int completed_iteration) { return idx_report_marshall2(); }
    // Entry point registration at startup
    
    static int reg_redn_wrapper_report_marshall2();
    // Entry point index lookup
    
    inline static int idx_redn_wrapper_report_marshall2() {
      static int epidx = reg_redn_wrapper_report_marshall2();
      return epidx;
    }
    
    static int redn_wrapper_report(CkReductionMsg* impl_msg) { return idx_redn_wrapper_report_marshall2(); }
    
    static void _call_redn_wrapper_report_marshall2(void* impl_msg, void* impl_obj_void);
    
    static void _call_report_marshall2(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_report_marshall2(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_report_marshall2(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_report_marshall2(PUP::er &p,void *msg);
    /* DECLS: Main(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Main_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_Main_CkMigrateMessage() {
      static int epidx = reg_Main_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_Main_CkMigrateMessage(); }
    
    static void _call_Main_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Main_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxy_Main:public CProxy_Chare{
  public:
    typedef Main local_t;
    typedef CkIndex_Main index_t;
    typedef CProxy_Main proxy_t;
    typedef CProxy_Main element_t;

    CProxy_Main(void) {};
    CProxy_Main(CkChareID __cid) : CProxy_Chare(__cid){  }
    CProxy_Main(const Chare *c) : CProxy_Chare(c){  }

    int ckIsDelegated(void) const
    { return CProxy_Chare::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_Chare::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_Chare::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_Chare::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_Chare::ckCheck(); }
    const CkChareID &ckGetChareID(void) const
    { return CProxy_Chare::ckGetChareID(); }
    operator const CkChareID &(void) const
    { return ckGetChareID(); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_Chare::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_Chare::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_Chare::pup(p);
    }

    void ckSetChareID(const CkChareID &c)
    {      CProxy_Chare::ckSetChareID(c); }
    Main *ckLocal(void) const
    { return (Main *)CkLocalChare(&ckGetChareID()); }
/* DECLS: Main(CkArgMsg* impl_msg);
 */
    static CkChareID ckNew(CkArgMsg* impl_msg, int onPE=CK_PE_ANY);
    static void ckNew(CkArgMsg* impl_msg, CkChareID* pcid, int onPE=CK_PE_ANY);
    CProxy_Main(CkArgMsg* impl_msg, int onPE=CK_PE_ANY);

/* DECLS: void report(int completed_iteration);
 */
    
    void report(int completed_iteration, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: Main(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_Main)
#define Main_SDAG_CODE 
typedef CBaseT1<Chare, CProxy_Main>CBase_Main;

/* DECLS: array Jacobi: ArrayElement{
Jacobi();
void begin_iteration();
void ghostsFromLeft(int width, const double *s);
void ghostsFromRight(int width, const double *s);
void ghostsFromTop(int width, const double *s);
void ghostsFromBottom(int width, const double *s);
Jacobi(CkMigrateMessage* impl_msg);
};
 */
 class Jacobi;
 class CkIndex_Jacobi;
 class CProxy_Jacobi;
 class CProxyElement_Jacobi;
 class CProxySection_Jacobi;
/* --------------- index object ------------------ */
class CkIndex_Jacobi:public CkIndex_ArrayElement{
  public:
    typedef Jacobi local_t;
    typedef CkIndex_Jacobi index_t;
    typedef CProxy_Jacobi proxy_t;
    typedef CProxyElement_Jacobi element_t;
    typedef CProxySection_Jacobi section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: Jacobi();
     */
    // Entry point registration at startup
    
    static int reg_Jacobi_void();
    // Entry point index lookup
    
    inline static int idx_Jacobi_void() {
      static int epidx = reg_Jacobi_void();
      return epidx;
    }

    
    static int ckNew() { return idx_Jacobi_void(); }
    
    static void _call_Jacobi_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Jacobi_void(void* impl_msg, void* impl_obj);
    /* DECLS: void begin_iteration();
     */
    // Entry point registration at startup
    
    static int reg_begin_iteration_void();
    // Entry point index lookup
    
    inline static int idx_begin_iteration_void() {
      static int epidx = reg_begin_iteration_void();
      return epidx;
    }

    
    inline static int idx_begin_iteration(void (Jacobi::*)() ) {
      return idx_begin_iteration_void();
    }


    
    static int begin_iteration() { return idx_begin_iteration_void(); }
    
    static void _call_begin_iteration_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_begin_iteration_void(void* impl_msg, void* impl_obj);
    /* DECLS: void ghostsFromLeft(int width, const double *s);
     */
    // Entry point registration at startup
    
    static int reg_ghostsFromLeft_marshall3();
    // Entry point index lookup
    
    inline static int idx_ghostsFromLeft_marshall3() {
      static int epidx = reg_ghostsFromLeft_marshall3();
      return epidx;
    }

    
    inline static int idx_ghostsFromLeft(void (Jacobi::*)(int width, const double *s) ) {
      return idx_ghostsFromLeft_marshall3();
    }


    
    static int ghostsFromLeft(int width, const double *s) { return idx_ghostsFromLeft_marshall3(); }
    
    static void _call_ghostsFromLeft_marshall3(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_ghostsFromLeft_marshall3(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_ghostsFromLeft_marshall3(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_ghostsFromLeft_marshall3(PUP::er &p,void *msg);
    /* DECLS: void ghostsFromRight(int width, const double *s);
     */
    // Entry point registration at startup
    
    static int reg_ghostsFromRight_marshall4();
    // Entry point index lookup
    
    inline static int idx_ghostsFromRight_marshall4() {
      static int epidx = reg_ghostsFromRight_marshall4();
      return epidx;
    }

    
    inline static int idx_ghostsFromRight(void (Jacobi::*)(int width, const double *s) ) {
      return idx_ghostsFromRight_marshall4();
    }


    
    static int ghostsFromRight(int width, const double *s) { return idx_ghostsFromRight_marshall4(); }
    
    static void _call_ghostsFromRight_marshall4(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_ghostsFromRight_marshall4(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_ghostsFromRight_marshall4(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_ghostsFromRight_marshall4(PUP::er &p,void *msg);
    /* DECLS: void ghostsFromTop(int width, const double *s);
     */
    // Entry point registration at startup
    
    static int reg_ghostsFromTop_marshall5();
    // Entry point index lookup
    
    inline static int idx_ghostsFromTop_marshall5() {
      static int epidx = reg_ghostsFromTop_marshall5();
      return epidx;
    }

    
    inline static int idx_ghostsFromTop(void (Jacobi::*)(int width, const double *s) ) {
      return idx_ghostsFromTop_marshall5();
    }


    
    static int ghostsFromTop(int width, const double *s) { return idx_ghostsFromTop_marshall5(); }
    
    static void _call_ghostsFromTop_marshall5(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_ghostsFromTop_marshall5(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_ghostsFromTop_marshall5(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_ghostsFromTop_marshall5(PUP::er &p,void *msg);
    /* DECLS: void ghostsFromBottom(int width, const double *s);
     */
    // Entry point registration at startup
    
    static int reg_ghostsFromBottom_marshall6();
    // Entry point index lookup
    
    inline static int idx_ghostsFromBottom_marshall6() {
      static int epidx = reg_ghostsFromBottom_marshall6();
      return epidx;
    }

    
    inline static int idx_ghostsFromBottom(void (Jacobi::*)(int width, const double *s) ) {
      return idx_ghostsFromBottom_marshall6();
    }


    
    static int ghostsFromBottom(int width, const double *s) { return idx_ghostsFromBottom_marshall6(); }
    
    static void _call_ghostsFromBottom_marshall6(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_ghostsFromBottom_marshall6(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_ghostsFromBottom_marshall6(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_ghostsFromBottom_marshall6(PUP::er &p,void *msg);
    /* DECLS: Jacobi(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Jacobi_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_Jacobi_CkMigrateMessage() {
      static int epidx = reg_Jacobi_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_Jacobi_CkMigrateMessage(); }
    
    static void _call_Jacobi_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Jacobi_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_Jacobi : public CProxyElement_ArrayElement{
  public:
    typedef Jacobi local_t;
    typedef CkIndex_Jacobi index_t;
    typedef CProxy_Jacobi proxy_t;
    typedef CProxyElement_Jacobi element_t;
    typedef CProxySection_Jacobi section_t;


    /* TRAM aggregators */

    CProxyElement_Jacobi(void) {
    }
    CProxyElement_Jacobi(const ArrayElement *e) : CProxyElement_ArrayElement(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_ArrayElement::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_ArrayElement::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_ArrayElement::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_ArrayElement::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_ArrayElement::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_ArrayElement::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_ArrayElement::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_ArrayElement::ckGetIndex(); }

    Jacobi *ckLocal(void) const
    { return (Jacobi *)CProxyElement_ArrayElement::ckLocal(); }

    CProxyElement_Jacobi(const CkArrayID &aid,const CkArrayIndex2D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_ArrayElement(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_Jacobi(const CkArrayID &aid,const CkArrayIndex2D &idx)
        :CProxyElement_ArrayElement(aid,idx)
    {
}

    CProxyElement_Jacobi(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_ArrayElement(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_Jacobi(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_ArrayElement(aid,idx)
    {
}
/* DECLS: Jacobi();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void begin_iteration();
 */
    
    void begin_iteration(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromLeft(int width, const double *s);
 */
    
    void ghostsFromLeft(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromRight(int width, const double *s);
 */
    
    void ghostsFromRight(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromTop(int width, const double *s);
 */
    
    void ghostsFromTop(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromBottom(int width, const double *s);
 */
    
    void ghostsFromBottom(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: Jacobi(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxyElement_Jacobi)
/* ---------------- collective proxy -------------- */
 class CProxy_Jacobi : public CProxy_ArrayElement{
  public:
    typedef Jacobi local_t;
    typedef CkIndex_Jacobi index_t;
    typedef CProxy_Jacobi proxy_t;
    typedef CProxyElement_Jacobi element_t;
    typedef CProxySection_Jacobi section_t;

    CProxy_Jacobi(void) {
    }
    CProxy_Jacobi(const ArrayElement *e) : CProxy_ArrayElement(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_ArrayElement::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_ArrayElement::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_ArrayElement::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_ArrayElement::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_Jacobi operator [] (const CkArrayIndex2D &idx) const
    { return CProxyElement_Jacobi(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_Jacobi operator() (const CkArrayIndex2D &idx) const
    { return CProxyElement_Jacobi(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_Jacobi operator () (int i0,int i1) const 
        {return CProxyElement_Jacobi(ckGetArrayID(), CkArrayIndex2D(i0,i1), CK_DELCTOR_CALL);}
    CProxyElement_Jacobi operator () (CkIndex2D idx) const 
        {return CProxyElement_Jacobi(ckGetArrayID(), CkArrayIndex2D(idx), CK_DELCTOR_CALL);}
    CProxy_Jacobi(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_ArrayElement(aid,CK_DELCTOR_ARGS) {}
    CProxy_Jacobi(const CkArrayID &aid) 
        :CProxy_ArrayElement(aid) {}
/* DECLS: Jacobi();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const int s2, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, const int s2, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void begin_iteration();
 */
    
    void begin_iteration(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromLeft(int width, const double *s);
 */
    
    void ghostsFromLeft(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromRight(int width, const double *s);
 */
    
    void ghostsFromRight(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromTop(int width, const double *s);
 */
    
    void ghostsFromTop(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromBottom(int width, const double *s);
 */
    
    void ghostsFromBottom(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: Jacobi(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_Jacobi)
/* ---------------- section proxy -------------- */
 class CProxySection_Jacobi : public CProxySection_ArrayElement{
  public:
    typedef Jacobi local_t;
    typedef CkIndex_Jacobi index_t;
    typedef CProxy_Jacobi proxy_t;
    typedef CProxyElement_Jacobi element_t;
    typedef CProxySection_Jacobi section_t;

    CProxySection_Jacobi(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_ArrayElement::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_ArrayElement::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_ArrayElement::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_ArrayElement::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_ArrayElement::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_ArrayElement::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_ArrayElement::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_ArrayElement::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_ArrayElement::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_ArrayElement::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_ArrayElement::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_ArrayElement::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_ArrayElement::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_ArrayElement::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_Jacobi operator [] (const CkArrayIndex2D &idx) const
        {return CProxyElement_Jacobi(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_Jacobi operator() (const CkArrayIndex2D &idx) const
        {return CProxyElement_Jacobi(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_Jacobi operator () (int idx) const 
        {return CProxyElement_Jacobi(ckGetArrayID(), *(CkArrayIndex2D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex2D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      CkVec<CkArrayIndex2D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          al.push_back(CkArrayIndex2D(i, j));
      return CkSectionID(aid, al.getVec(), al.size(), factor);
    } 
    CProxySection_Jacobi(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_Jacobi(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_ArrayElement(aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_Jacobi(const CkSectionID &sid)  
        :CProxySection_ArrayElement(sid) { ckAutoDelegate(); }
    CProxySection_Jacobi(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_Jacobi(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_ArrayElement(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_Jacobi(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_ArrayElement(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_ArrayElement::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_ArrayElement::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_ArrayElement::resetSection();
    } 
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: Jacobi();
 */
    

/* DECLS: void begin_iteration();
 */
    
    void begin_iteration(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromLeft(int width, const double *s);
 */
    
    void ghostsFromLeft(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromRight(int width, const double *s);
 */
    
    void ghostsFromRight(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromTop(int width, const double *s);
 */
    
    void ghostsFromTop(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void ghostsFromBottom(int width, const double *s);
 */
    
    void ghostsFromBottom(int width, const double *s, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: Jacobi(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxySection_Jacobi)
#define Jacobi_SDAG_CODE 
typedef CBaseT1<ArrayElementT<CkIndex2D>, CProxy_Jacobi>CBase_Jacobi;








/* ---------------- method closures -------------- */
class Closure_Main {
  public:


    struct report_2_closure;


};

/* ---------------- method closures -------------- */
class Closure_Jacobi {
  public:


    struct begin_iteration_2_closure;


    struct ghostsFromLeft_3_closure;


    struct ghostsFromRight_4_closure;


    struct ghostsFromTop_5_closure;


    struct ghostsFromBottom_6_closure;


};

extern void _registerjacobi2d(void);
extern "C" void CkRegisterMainModule(void);
#endif
