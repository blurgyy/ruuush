#include <bits/stdc++.h>
using namespace std;

typedef vector<array<int,4>> testcase;
array<int,4> blank = {0,0,0,0};

const int dx[] = {1,0,-1,0}, dy[] = {0,1,0,-1};

random_device rd;

testcase rectangle(int h = -1, int w = -1) {
	if (h == -1 && w == -1) cin >> h >> w;
	auto I = [&](int i, int j) { return i*w + j; };
	int k = 0;
	testcase res(h*w,blank);
	for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			if (x+1 < h) res[I(x,y)][2] = res[I(x+1,y)][0] = ++k;
			if (y+1 < w) res[I(x,y)][1] = res[I(x,y+1)][3] = ++k;
		}
	}
	return res;
}

testcase torus() {
	int h, w; cin >> h >> w;
	auto I = [&](int i, int j) { return i*w + j; };
	int k = 0;
	testcase res(h*w,blank);
	for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			res[I(x,y)][2] = res[I((x+1)%h,y)][0] = ++k;
			res[I(x,y)][1] = res[I(x,(y+1)%w)][3] = ++k;
		}
	}
	return res;
}

testcase from_coords(vector<pair<int,int>> i2p) {
	map<pair<int,int>,int> p2i;
	
	int n = i2p.size(), k = 0;
	for (int i = 0; i < n; i++) p2i[i2p[i]] = i;

	testcase res(n,blank);
	for (int i = 0; i < i2p.size(); i++) {
		int x, y;
		tie(x,y) = i2p[i];
		for (int dir = 0; dir < 4; dir++) {
			auto p = make_pair(x+dx[dir],y+dy[dir]);
			if (p2i.count(p)) {
				int j = p2i[p];
				if (i < j) res[i][dir] = res[j][dir^2] = ++k;
			}
		}
	}
	return res;
}

testcase chaos() {
	int n; cin >> n;
	
	testcase res(n);
	vector<int> cnt(n);
	int k = 0;
	for (int j = 1; j < n; j++) {
		int i = -1;
		do i = rand() % j; while (cnt[i] == 4);
		res[i][cnt[i]++] = res[j][cnt[j]++] = ++k;
	}
	for (auto &p: res) shuffle(begin(p),end(p),rd);
	return res;
}

testcase zigzag() {
	int n = 100000;
	vector<pair<int,int>> p;
	for (int x = 0; x < n/2; x++) {
		p.emplace_back(x,x);
		p.emplace_back(x,x+1);
	}
	return from_coords(p);
}

testcase overflow() {
	// 60455 * 71049 == 299999 (in signed 32-bit)
	// 50128 * 85682 == 100000 (in signed 32-bit)
	int h = 60455, w = 71049, n = 299999;
	assert(h*w == n);
	
	vector<pair<int,int>> p;
	for (int t = 0; p.size() < n; t++) {
		for (int x = t; x < h-t-1; x++) p.emplace_back(x,t);
		for (int y = t; y < w-t-1; y++) p.emplace_back(h-t-1,y);
		for (int x = h-t-1; x > 0; x--) p.emplace_back(x,w-t-1);
		for (int y = w-t-1; y > 0; y--) p.emplace_back(t,y);
	}
	p.resize(n);
	return from_coords(p);
}

testcase frame() {
	int d; cin >> d;
	int n = 300000/(4*d);
	vector<pair<int,int>> p;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < d; y++) {
			p.emplace_back(x,y);
			p.emplace_back(x,n-1-y);
		}
	}
	for (int y = d; y < n-d; y++) {
		for (int x = 0; x < d; x++) {
			p.emplace_back(x,y);
			p.emplace_back(n-1-x,y);
		}
	}
	return from_coords(p);
}

void randomize(testcase &tc) {
	int k = 0;
	for (auto a: tc) for (int x: a) k = max(k,x);

	vector<int> e(k);
	iota(begin(e),end(e),1);
	shuffle(begin(e),end(e),rd);
	shuffle(begin(tc),end(tc),rd);
	for (auto &a: tc) {
		for (int &x: a) if (x > 0) x = e[x-1];
		int rot = rand() % 4;
		while (rot--) swap(a[0],a[1]), swap(a[1],a[2]), swap(a[2],a[3]);
	}
}

testcase mutations() {
	int r = 1 + rand() % 2;
	testcase res = rectangle(2,3);
	randomize(res);
	int n = res.size();
	int k = 0;
	for (auto row: res) for (int x: row) k = max(k,x);

	while (r--) {
		int type = rand() % 3;
		
		auto rand_edge = [&](int &i, int &j) {
			i = rand() % n, j = rand() % 4;
		};
		
		int i1, j1, i2, j2;

		if (type == 0) {
			rand_edge(i1,j1), rand_edge(i2,j2);
			swap(res[i1][j1],res[i2][j2]);
		} else if (type == 1) {
			do rand_edge(i1,j1); while (res[i1][j1] > 0);
			do rand_edge(i2,j2); while ((i1 == i2 && j1 == j2) || res[i2][j2] > 0);
			res[i1][j1] = res[i2][j2] = ++k;
		} else {
			for (auto &row: res) for (int &x: row) if (x == k) x = 0;
			k--;
		}
	}
	
	bool ok = true;
	for (auto row: res) {
		for (int a = 0; a < 4; a++) {
			for (int b = a+1; b < 4; b++) {
				if (row[a] > 0 && row[a] == row[b]) ok = false;
			}
		}
	}	
	
	if (!ok) res = mutations();
	return res;
}

int main() {
	srand(rd());
	
	string type;
	cin >> type;

	testcase tc;
	if (type == "valid") {
		tc = rectangle();
		randomize(tc);
	}
	if (type == "torus") {
		tc = torus();
		randomize(tc);
	}
	if (type == "zig-zag") {
		tc = zigzag();
	}
	if (type == "overflow") {
		tc = overflow();
	}
	if (type == "frame") {
		tc = frame();
	}
	if (type == "chaos") {
		tc = chaos();
	}
	if (type == "mutations") {
		tc = mutations();
		randomize(tc);
	}

	cout << tc.size() << endl;
	for (auto a: tc) for (int i = 0; i < 4; i++) cout << a[i] << " \n"[i==3];
}
