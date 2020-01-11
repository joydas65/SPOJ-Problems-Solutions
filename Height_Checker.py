class Solution:
    def heightChecker(self, heights: List[int]) -> int:
        
        n = len(heights)
        
        if n == 0:
            return 0
        
        arr,ans = sorted(heights),0
        
        for i,j in enumerate(arr):
            
            if j != heights[i]:
                
                ans += 1
                
        return ans
