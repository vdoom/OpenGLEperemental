#ifndef CTFASTDELEGAT_H
#define CTFASTDELEGAT_H
#include "QDebug"
//  Контейнер для хранения до 2-х аргументов.
struct NIL {};

class IArguments
{
public:
    virtual ~IArguments() {}
};

template< class T1 = NIL, class T2 = NIL > class Arguments : public IArguments
{
public:
      T1 arg1;
      T2 arg2;

      Arguments()
      {}
      Arguments( T1 i_arg1 ) : arg1( i_arg1 )
      {}
      Arguments( T1 i_arg1, T2 i_arg2 ) : arg1( i_arg1 ), arg2( i_arg2 )
      {}
};

//  Контейнер для хранения указателя на метод.
class IContainer
{
public:
    virtual void Call( IArguments* ) = 0;
};

template< class T, class M > class Container : public IContainer
{

private:

    typedef void (T::*U)(void);
    T* m_class; U m_method;

public:

    Container()
    {}
    Container( T* c, M m ) : m_class( c ), m_method( m )
    {}
    virtual void Call( IArguments* i_args )
    {
      (m_class->*m_method)();
    }
};

  //Специализация для метода без аргументов.
//template< class T, class M >
//  class Container< T, void (T::*)(void) > : public IContainer
//{
//  typedef void (T::*U)(void);
//  public: Container( T* c, M m ) : m_class( c ), m_method( m ) {}
//  private: T* m_class; U m_method;
//  public: virtual void Call( IArguments* i_args )
//  {
//    (m_class->*m_method)();
//  }
//};

//  Специализация для метода с одним аргументом.
template< class T, class A1 > class Container< T, void (T::*)(A1) > : public IContainer
{
private:
    typedef void (T::*M)(A1);
    typedef Arguments<A1> A;

    T* m_class; M m_method;
public:
    Container( T* c, M m ) : m_class( c ), m_method( m )
    {}
    virtual void Call( IArguments* i_args )
    {
        A* a = dynamic_cast< A* >( i_args );
        //assert( a );
        if( a ) (m_class->*m_method)( a->arg1 );
    }
};

//  Специализация для метода с двумя аргументами
template< class T, class A1, class A2 > class Container< T, void (T::*)(A1,A2) > : public IContainer
{
private:
    typedef void (T::*M)(A1,A2);
    typedef Arguments<A1,A2> A;
    T* m_class; M m_method;
  public:
    Container( T* c, M m ) : m_class( c ), m_method( m ) {}
    virtual void Call( IArguments* i_args )
    {
        A* a = dynamic_cast< A* >( i_args );
        //assert( a );
        if( a ) (m_class->*m_method)( a->arg1, a->arg2 );
    }
};

//  Собственно делегат.
class ctFastDelegat
{

private:
  //TODO: NEED REFINE FOR LIST OF CONTAINERS
  IContainer* m_container;

public:

  ctFastDelegat() : m_container( 0 ) {}
  ~ctFastDelegat() { if( m_container ) delete m_container; }

  template< class T, class U > void Connect( T* i_class, U i_method )
  {
    if( m_container ) delete m_container;
    m_container = new Container< T, U >( i_class, i_method );
  }

  void operator()()
  {
      Arguments<>* t_args = new Arguments<>();
    m_container->Call( t_args);
  }

  template< class T1 > void operator()( T1 i_arg1 )
  {
      Arguments<T1>* t_args = new Arguments< T1 >( i_arg1 );
    m_container->Call(t_args  );
  }

  template< class T1, class T2 > void operator()( T1 i_arg1, T2 i_arg2 )
  {
    m_container->Call( & Arguments< T1, T2 >( i_arg1, i_arg2 ) );
  }
};

#endif // CTFASTDELEGAT_H


//class ctFastDelegat
//{
////public:
////    ctFastDelegat();

////    template <class T, void (T::*TMethod)(int)>
////    static ctFastDelegat from_method(T* object_ptr)
////    {
////        ctFastDelegat d;
////        d.object_ptr = object_ptr;
////        d.stub_ptr = &method_stub<T, TMethod>; // #1
////        return d;
////    }

////    void operator()(int a1) const
////    {
////        return (*stub_ptr)(object_ptr, a1);
////    }

////private:
////    typedef void (*stub_type)(void* object_ptr, int);

////    void* object_ptr;
////    stub_type stub_ptr;

////    template <class T, void (T::*TMethod)(int)>
////    static void method_stub(void* object_ptr, int a1)
////    {
////        T* p = static_cast<T*>(object_ptr);
////        return (p->*TMethod)(a1); // #2
////    }
//public:
//  ctFastDelegat()
//    : object_ptr(0)
//    , stub_ptr(0)
//  {}

//  template < class T, void (T::*TMethod)(int) >
//    static ctFastDelegat from_method(T* object_ptr)
//  {
//    ctFastDelegat d;
//    d.object_ptr = object_ptr;
//    d.stub_ptr = &delegate_stub_t< T, TMethod >::method_stub; // #1

//    return d;
//  }

//  void operator()(int a1) const
//  {
//    return (*stub_ptr)(object_ptr, a1);
//  }

//private:
//  typedef void (*stub_type)(void* object_ptr, int);

//  void* object_ptr;
//  stub_type stub_ptr;

//  template < class T, void (T::*TMethod)(int) >
//  struct delegate_stub_t
//  {
//    static void method_stub(void* object_ptr, int a1)
//    {
//      T* p = static_cast< T* >(object_ptr);
//      return (p->*TMethod)(a1); // #2

//    }
//  };
//};
