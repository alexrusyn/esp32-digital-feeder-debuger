import { Input, Listbox, useFilter, useListCollection } from "@chakra-ui/react";

const SelectList = ({ value, setValue, placeholder, items, title = null }) => {
  const { contains } = useFilter({ sensitivity: "base" });

  const { collection, filter } = useListCollection({
    initialItems: items,
    filter: contains,
    groupBy: (item) => item.type,
  });

  return (
    <Listbox.Root
      value={value}
      collection={collection}
      onValueChange={(details) => setValue(details.value)}
    >
      {title && <Listbox.Label>{title}</Listbox.Label>}
      <Listbox.Input
        as={Input}
        placeholder={placeholder}
        onChange={(e) => filter(e.target.value)}
      />
      <Listbox.Content divideY="1px">
        {collection.group().map(([category, items]) => (
          <Listbox.ItemGroup key={category}>
            <Listbox.ItemGroupLabel>{category}</Listbox.ItemGroupLabel>
            {items.map((item) => (
              <Listbox.Item item={item} key={item.value}>
                <Listbox.ItemText>{item.label}</Listbox.ItemText>
                <Listbox.ItemIndicator />
              </Listbox.Item>
            ))}
          </Listbox.ItemGroup>
        ))}
      </Listbox.Content>
    </Listbox.Root>
  );
};

export default SelectList;
