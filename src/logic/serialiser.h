// Copyright 2023 Nicholas Mazey. All rights reserved
#include <tuple>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#ifndef GAME_ENGINE_LOGIC_SERIALISER_H
#define GAME_ENGINE_LOGIC_SERIALISER_H

namespace boost
{
    namespace serialization
    {
        template <class Archive>
        void serialize(Archive &ar, std::tuple<int, int, int> &tuple, const unsigned int version)
        {
            ar &std::get<0>(tuple);
            ar &std::get<1>(tuple);
            ar &std::get<2>(tuple);
        }
    } // namespace serialization
} // namespace boost
#endif // GAME_ENGINE_LOGIC_SERIALISER_H