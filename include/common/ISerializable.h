#pragma once

namespace Akr {
template <typename InputType>
class ISerializable
{
  public:
  virtual ~ISerializable() = default;

  virtual void Serialize(InputType& output) = 0;
  virtual void Deserialize(const InputType& input) = 0;
};
}