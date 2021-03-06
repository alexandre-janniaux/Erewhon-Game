// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Server" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef EREWHON_SERVER_ARENA_HPP
#define EREWHON_SERVER_ARENA_HPP

#include <Nazara/Core/Clock.hpp>
#include <NDK/EntityList.hpp>
#include <NDK/World.hpp>
#include <Shared/NetworkReactor.hpp>
#include <Shared/Protocol/Packets.hpp>
#include <Server/ServerCommandStore.hpp>
#include <unordered_set>

namespace ewn
{
	class ServerApplication;
	class Player;

	class Arena
	{
		friend Player;

		public:
			Arena(ServerApplication* app);
			~Arena() = default;

			const Ndk::EntityHandle& CreatePlayerSpaceship(Player* owner);

			void DispatchChatMessage(Player* player, const Nz::String& message);

			void Update(float elapsedTime);

		private:
			void HandlePlayerLeave(Player* player);
			void HandlePlayerJoin(Player* player);
			void OnSpaceshipDestroy(Ndk::Entity* spaceship);

			Nz::Clock m_stateClock;
			Nz::UdpSocket m_debugSocket;
			Ndk::EntityList m_spaceships;
			Ndk::World m_world;
			std::unordered_map<Player*, Ndk::EntityHandle> m_players;
			Packets::ArenaState m_arenaStatePacket;
			ServerApplication* m_app;
			Nz::UInt8 m_stateId;
			float m_ghostBroadcastAccumulator;
			float m_stateBroadcastAccumulator;
	};
}

#include <Server/Arena.inl>

#endif // EREWHON_SERVER_ARENA_HPP
