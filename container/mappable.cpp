namespace lasd {

    /* ************************************************************************** */

    // PreOrderMappableContainer

    // Specific member function (inherited from MappableContainer)

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFun fun) {
        PreOrderMap(fun);
    }

    // PostOrderMappableContainer

    // Specific member function (inherited from MappableContainer)

    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFun fun) {
        PostOrderMap(fun);
    }

    /* ************************************************************************** */

}