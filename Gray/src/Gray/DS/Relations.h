#pragma once

#include <vector>
#include <assert.h>
namespace Gray
{
	using uint = unsigned int;
	template <typename _First, typename... _Rest>
	struct Table;

	template <typename T>
	struct Table<T>;

	template<typename T>
	struct EntityIndex;

	template<typename T, typename _First, typename... _Rest>
	class EntityData;

	template<typename X, typename _First, typename... _Rest>
	struct GetImpl;

	template<typename X, typename... _Rest>
	struct GetImpl<X, X, _Rest...>;

	template<typename _First, typename... _Rest>
	struct AddImpl;

	template<typename _Only>
	struct AddImpl<_Only>;

	template<typename _First, typename... _Rest>
	struct RemoveImpl;

	template<typename _Only>
	struct RemoveImpl<_Only>;

	template<typename _First, typename... _Rest>
	void Add(Table< typename std::remove_reference<_First>::type, typename std::remove_reference<_Rest...>::type >& t, _First&& fval, _Rest&&... rval);

	template <typename T>
	class FixedVector
	{
	public:
		FixedVector(std::vector<T>& v)
			: vec{v}
		{
		}

		T& operator[](size_t s)
		{
			return vec[s];
		}

		const T& operator[](size_t s) const
		{
			return vec[s];
		}

		size_t Size() const
		{
			return vec.size();
		}

		size_t Capacity() const
		{
			return vec.capacity();
		}

		friend bool operator==(const FixedVector<T>& t1, const FixedVector<T>& t2)
		{
			return &(t1.vec) == &(t2.vec);
		}

	private:
		std::vector<T>& vec;
	};

	
	template<typename T>
	struct EntityIndex
	{
		int index;

		friend bool operator==(const EntityIndex<T>& t1, const EntityIndex<T>& t2)
		{
			return t1.index == t2.index;
		}

		friend bool operator!=(const EntityIndex<T>& t1, const EntityIndex<T>& t2)
		{
			return t1.index != t2.index;
		}
	};

	template<typename T>
	const EntityIndex<T> NullIndex()
	{
		return EntityIndex<T> {0};
	}
	template<typename T>
	struct Entity
	{
		int id;

		friend bool operator==(const Entity<T>& t1, const Entity<T>& t2)
		{
			return t1.id == t2.id;
		}

		friend bool operator!=(const Entity<T>& t1, const Entity<T>& t2)
		{
			return t1.id != t2.id;
		}
	};

	template<typename T, typename _First, typename... _Rest>
	class EntityData
	{
	public:
		template<typename _VFirst, typename... _VRest>
		EntityData(_VFirst&& fval, _VRest&&... restval)
		{
			AddRow(std::forward<_VFirst>(fval), std::forward<_VRest>(restval)...);
		}
	
		EntityIndex<T> IndexOf(const Entity<T>& entity)
		{
			if (idToIndexMap.find(entity.id) == idToIndexMap.end())
				return EntityIndex<T> { 0 };
			else
				return EntityIndex<T> {idToIndexMap[entity.id]};
		}

		template<typename _VFirst, typename... _VRest>
		void AddRow(_VFirst&& fval, _VRest&&... restval)
		{
			static int lastID = -1;
			Add(table, std::forward<_VFirst>(fval), std::forward<_VRest>(restval)...);
			idToIndexMap[++lastID] = GetLastEntityIndex().index;
		}

		void Delete(const Entity<T>& entity)
		{
			Delete(EntityIndex<T> { IndexOf(entity) });
		}

		void Delete(const EntityIndex<T>& eIndex)
		{
			const EntityIndex<T> nIndex = { 0 };
			assert(eIndex != nIndex);

			EntityIndex<T> oldLast = GetLastEntityIndex();
			RemoveImpl<_First, _Rest...>::RemoveRow(static_cast<uint>(eIndex.index), table);
	
			if (oldLast == eIndex)
			{
				for (std::vector<EntityIndex<T>>* dep_ptr : dependents)
				{
					for (EntityIndex<T>& refEntity : *dep_ptr)
					{
						if (refEntity == eIndex)
						{
							refEntity = nIndex;
						}
					}
				}

				for (auto it = idToIndexMap.begin(); it != idToIndexMap.end(); it++)
				{
					if (it->second == eIndex.index)
						idToIndexMap.erase(it++);
				}
			}

			else
			{
				for (std::vector<EntityIndex<T>>* dep_ptr : dependents)
				{
					for (EntityIndex<T>& refEntity : *dep_ptr)
					{
						if (refEntity == eIndex)
						{
							refEntity = nIndex;
						}

						else if (refEntity == oldLast)
						{
							refEntity = nIndex;
						}
					}

					for (auto it = idToIndexMap.begin(); it != idToIndexMap.end(); it++)
					{
						if (it->second == oldLast.index)
							it->second = eIndex.index;

						else if (it->second == eIndex.index)
							idToIndexMap.erase(it++);
					}
				}


			}

		
		}

		EntityIndex<T> GetLastEntityIndex()
		{
			return EntityIndex<T> { static_cast<int>(table.vec.size() - 1) };
		}

		void AddDependent(const FixedVector<EntityIndex<T>>& v)
		{
			dependents.push_back(v);
		}


		void RemoveDependent(const FixedVector<EntityIndex<T>>& v)
		{
			for (FixedVector<EntityIndex<T>>& dep : dependents)
			{
				if (dep == v)
				{
					dep = dependents.back();
					dependents.pop_back();
				}
			}
		}

		template<typename X>
		FixedVector<X> GetField()
		{
			return FixedVector{ ::GetField<X>(table) };
		}

		size_t GetSize()
		{
			return table.vec.size();
		}

	private:
	
		struct EntityID
		{
			int id;
		};

		std::unordered_map<int, int> idToIndexMap;
		Table<_First, _Rest...> table;
		std::vector < FixedVector<EntityIndex<T>> > dependents;
	};

	template <typename _First, typename... _Rest>
	struct Table
	{
		using type = _First;
		
		std::vector<_First> vec;
		Table<_Rest...> next;

	};

	template <typename T>
	struct Table<T>
	{
		using type = T;
		std::vector<T> vec;
	};

	template<typename X, typename _First, typename... _Rest>
	std::vector<X>& GetField(Table< _First, _Rest... >& t)
	{
		return GetImpl<X, _First, _Rest...>::GetVec(t);
	}

	template<typename _First, typename... _Rest>
	void Add(Table< typename std::remove_reference<_First>::type, typename std::remove_reference<_Rest>::type... >& t, _First&& fval, _Rest&&... rval)
	{
		AddImpl<_First, _Rest...>::AddToField(t, std::forward<_First>(fval), std::forward<_Rest>(rval)...);
	}

	template<typename _Only>
	void Add(Table< typename std::remove_reference<_Only>::type>& t, _Only&& only)
	{
		AddImpl<_Only>::AddToField(t, std::forward<_Only>(only));
	}

	template<typename X, typename _First, typename... _Rest>
	struct GetImpl
	{
		static std::vector<X>& GetVec(Table<_First, _Rest...>& t)
		{
			return GetImpl<X, _Rest...>::GetVec(t.next);
		}
	};

	template<typename X, typename... _Rest>
	struct GetImpl<X, X, _Rest...>
	{
		static std::vector<X>& GetVec(Table<X, _Rest...>& t)
		{
			return t.vec;
		}
	};

	template<typename _First, typename... _Rest>
	struct AddImpl
	{
		static void AddToField(Table <typename std::remove_reference<_First>::type,
			typename std::remove_reference<_Rest>::type...>& t, _First&& fval, _Rest&&... rstvals)
		{
			t.vec.push_back(fval);
			AddImpl<_Rest...>::AddToField(t.next, std::forward<_Rest>(rstvals)...);
		}
	};

	template<typename _Only>
	struct AddImpl<_Only>
	{
		static void AddToField(Table<typename std::remove_reference<_Only>::type>& t, _Only&& val)
		{
			t.vec.push_back(val);
		}
	};

	template<typename _First, typename... _Rest>
	struct RemoveImpl
	{
		static void RemoveRow(uint row, Table<_First, _Rest...>& t)
		{
			assert(row < t.vec.size());
			t.vec[row] = t.vec.back();
			t.vec.pop_back();
			RemoveImpl<_Rest...>::RemoveRow(row, t.next);
		}
	};

	template<typename _Only>
	struct RemoveImpl<_Only>
	{
		static void RemoveRow(uint row, Table<_Only>& t)
		{
			assert(row < t.vec.size());
			t.vec[row] = t.vec.back();
			t.vec.pop_back();
		}
	};

	struct Simple
	{
		std::vector<int> i1;
		std::vector<int> i2;

		void Insert(int c, int e)
		{
			if (c == 0)
				i1.push_back(e);

			else
				i2.push_back(e);
		}
	};

}