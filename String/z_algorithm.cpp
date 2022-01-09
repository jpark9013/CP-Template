std::vector<int> Z(const std::string str) {
  int n = str.size();
  std::vector<int> res(n);
  res[0] = n;
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && str[j] == str[i + j]) j++;
    res[i] = j;
    if (j == 0) {
      i++;
      continue;
    }
    int k = 1;
    while (i + k < n && k + res[k] < j) {
    	res[i + k] = res[k];
    	k++;
    }
    i += k;
    j -= k;
  }
  return res;
};
