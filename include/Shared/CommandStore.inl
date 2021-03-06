// Copyright (C) 2017 J�r�me Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Shared/CommandStore.hpp>
#include <cassert>
#include <iostream>

namespace ewn
{
	template<typename T>
	const CommandStore::IncomingCommand& CommandStore::GetIncomingCommand() const
	{
		const std::size_t packetId = static_cast<std::size_t>(T::Type);
		assert(m_incomingCommands.size() > packetId);

		const IncomingCommand& command = m_incomingCommands[packetId];
		assert(command.enabled);

		return command;
	}

	template<typename T>
	const CommandStore::OutgoingCommand& CommandStore::GetOutgoingCommand() const
	{
		const std::size_t packetId = static_cast<std::size_t>(T::Type);
		assert(m_outgoingCommands.size() > packetId);

		const OutgoingCommand& command = m_outgoingCommands[packetId];
		assert(command.enabled);

		return command;
	}

	template<typename T, typename CB>
	void CommandStore::RegisterIncomingCommand(const char* name, CB&& callback)
	{
		std::size_t packetId = static_cast<std::size_t>(T::Type);

		IncomingCommand newCommand;
		newCommand.enabled = true;
		newCommand.unserialize = [cb = std::forward<CB>(callback)](std::size_t peerId, Nz::NetPacket&& packet)
		{
			T data;
			try
			{
				Packets::Unserialize(packet, data);
			}
			catch (const std::exception&)
			{
				std::cerr << "Failed to unserialize packet" << std::endl;
				return false;
			}

			cb(peerId, data);
			return true;
		};
		newCommand.name = name;

		if (m_incomingCommands.size() <= packetId)
			m_incomingCommands.resize(packetId + 1);

		m_incomingCommands[packetId] = std::move(newCommand);
	}

	template<typename T>
	void CommandStore::RegisterOutgoingCommand(const char* name, Nz::ENetPacketFlags flags, Nz::UInt8 channelId)
	{
		std::size_t packetId = static_cast<std::size_t>(T::Type);

		OutgoingCommand newCommand;
		newCommand.channelId = channelId;
		newCommand.enabled = true;
		newCommand.flags = flags;
		newCommand.name = name;

		if (m_outgoingCommands.size() <= packetId)
			m_outgoingCommands.resize(packetId + 1);

		m_outgoingCommands[packetId] = std::move(newCommand);
	}

	template<typename T>
	void CommandStore::SerializePacket(Nz::NetPacket& packet, const T& data) const
	{
		packet << static_cast<Nz::UInt8>(T::Type);

		Packets::Serialize(packet, data);
	}
}